// Copyright (c) 2017-2018, The Monero Project
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#include <vector>
#include <unordered_map>
#include <boost/uuid/nil_generator.hpp>
#include "string_tools.h"
#include "cryptonote_protocol_defs.h"
#include "block_queue.h"
#include "sync_lock.h"

#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "cn.block_queue"

namespace std {
  static_assert(sizeof(size_t) <= sizeof(boost::uuids::uuid), "boost::uuids::uuid too small");
  template<> struct hash<boost::uuids::uuid> {
    std::size_t operator()(const boost::uuids::uuid &_v) const {
      return reinterpret_cast<const std::size_t &>(_v);
    }
  };
}

namespace cryptonote
{

void block_queue::add_blocks(uint64_t height, std::list<cryptonote::block_complete_entry> bcel, const boost::uuids::uuid &connection_id, float rate, size_t size)
{
  if (m_sync_lock.try_lock()) {
    std::list<crypto::hash> hashes;
    bool has_hashes = remove_span(height, &hashes);
    blocks.insert(span(height, std::move(bcel), connection_id, rate, size));
    if (has_hashes)
    set_span_hashes(height, connection_id, hashes);
    m_sync_lock.unlock();
  }
  return;
}

void block_queue::add_blocks(uint64_t height, uint64_t nblocks, const boost::uuids::uuid &connection_id, boost::posix_time::ptime time)
{
  CHECK_AND_ASSERT_THROW_MES(nblocks > 0, "Empty span");
  if (m_sync_lock.try_lock()) {
    blocks.insert(span(height, nblocks, connection_id, time));
    m_sync_lock.unlock();
  }
  return;
}

void block_queue::flush_spans(const boost::uuids::uuid &connection_id, bool all)
{
  if (m_sync_lock.try_lock()) {
    block_map::iterator i = blocks.begin();
    while (i != blocks.end())
    {
      block_map::iterator j = i++;
      if (j->connection_id == connection_id && (all || j->blocks.size() == 0))
      {
        blocks.erase(j);
      }
    }
    m_sync_lock.unlock();
  }
  return;
}

void block_queue::flush_stale_spans(const std::set<boost::uuids::uuid> &live_connections)
{
  if (m_sync_lock.try_lock()) {
    block_map::iterator i = blocks.begin();
    if (i != blocks.end() && is_blockchain_placeholder(*i))
      ++i;
    while (i != blocks.end())
    {
      block_map::iterator j = i++;
      if (live_connections.find(j->connection_id) == live_connections.end() && j->blocks.size() == 0)
      {
        blocks.erase(j);
      }
    }
    m_sync_lock.unlock();
  }
  return;
}

bool block_queue::remove_span(uint64_t start_block_height, std::list<crypto::hash> *hashes)
{
  if (m_sync_lock.try_lock()) {
    for (block_map::iterator i = blocks.begin(); i != blocks.end(); ++i)
    {
      if (i->start_block_height == start_block_height)
      {
        if (hashes)
          *hashes = std::move(i->hashes);
        blocks.erase(i);
        m_sync_lock.unlock();
        return true;
      }
    }
    m_sync_lock.unlock();
  }
  return false;
}

void block_queue::remove_spans(const boost::uuids::uuid &connection_id, uint64_t start_block_height)
{
  if (m_sync_lock.try_lock()) {
    for (block_map::iterator i = blocks.begin(); i != blocks.end(); )
    {
      block_map::iterator j = i++;
      if (j->connection_id == connection_id && j->start_block_height <= start_block_height)
      {
        blocks.erase(j);
      }
    }
    m_sync_lock.unlock();
  }
  return;
}

uint64_t block_queue::get_max_block_height() const
{
  uint64_t height = 0;
  if (m_sync_lock.try_lock()) {
    for (const auto &span: blocks)
    {
      const uint64_t h = span.start_block_height + span.nblocks - 1;
      if (h > height)
        height = h;
    }
    m_sync_lock.unlock();
  }
  return height;
}

void block_queue::print() const
{
  if (m_sync_lock.try_lock()) {
    MDEBUG("Block queue has " << blocks.size() << " spans");
    for (const auto &span: blocks)
      MDEBUG("  " << span.start_block_height << " - " << (span.start_block_height+span.nblocks-1) << " (" << span.nblocks << ") - " << (is_blockchain_placeholder(span) ? "blockchain" : span.blocks.empty() ? "scheduled" : "filled    ") << "  " << span.connection_id << " (" << ((unsigned)(span.rate*10/1024.f))/10.f << " kB/s)");
    m_sync_lock.unlock();
  }
  return;
}

std::string block_queue::get_overview() const
{
  std::string s = "[]";
  if (m_sync_lock.try_lock()) {
  if (blocks.empty()) {
    m_sync_lock.unlock();
    return s;
  }
  block_map::const_iterator i = blocks.begin();
  s = std::string("[") + std::to_string(i->start_block_height + i->nblocks - 1) + ":";
  while (++i != blocks.end())
    s += i->blocks.empty() ? "." : "o";
  s += "]";
  m_sync_lock.unlock();
  }
  return s;
}

bool block_queue::requested(const crypto::hash &hash) const
{
  if (m_sync_lock.try_lock()) {
  for (const auto &span: blocks)
  {
    for (const auto &h: span.hashes)
    {
      if (h == hash) {
        m_sync_lock.unlock();
        return true;
      }
    }
  }
  }
  return false;
}

std::pair<uint64_t, uint64_t> block_queue::reserve_span(uint64_t first_block_height, uint64_t last_block_height, uint64_t max_blocks, const boost::uuids::uuid &connection_id, const std::list<crypto::hash> &block_hashes, boost::posix_time::ptime time)
{

  uint64_t span_start_height = 0;
  uint64_t span_length = 0;
  std::pair<uint64_t,uint64_t> height_length = { 0 , 0 };
  if (m_sync_lock.try_lock()) {

  if (last_block_height < first_block_height || max_blocks == 0)
  {
    MDEBUG("reserve_span: early out: first_block_height " << first_block_height << ", last_block_height " << last_block_height << ", max_blocks " << max_blocks);
    m_sync_lock.unlock();
    return height_length;
  }

  span_start_height = last_block_height - block_hashes.size() + 1;
  std::list<crypto::hash>::const_iterator i = block_hashes.begin();
  while (i != block_hashes.end() && requested(*i))
  {
    ++i;
    ++span_start_height;
  }
  uint64_t span_length = 0;
  std::list<crypto::hash> hashes;
  while (i != block_hashes.end() && span_length < max_blocks)
  {
    hashes.push_back(*i);
    ++i;
    ++span_length;
  }
  if (span_length == 0) {
    m_sync_lock.unlock();
    return height_length;
  }
  MDEBUG("Reserving span " << span_start_height << " - " << (span_start_height + span_length - 1) << " for " << connection_id);
  add_blocks(span_start_height, span_length, connection_id, time);
  set_span_hashes(span_start_height, connection_id, hashes);
  m_sync_lock.unlock();
  }
  height_length.first = span_start_height;
  height_length.second = span_length;
  return height_length;
}

bool block_queue::is_blockchain_placeholder(const span &span) const
{
  return span.connection_id == boost::uuids::nil_uuid();
}

std::pair<uint64_t, uint64_t> block_queue::get_start_gap_span() const
{
  uint64_t current_height = 0;
  uint64_t first_span_height = 0;
  std::pair<uint64_t,uint64_t> span_pair = { 0, 0 };
  if (m_sync_lock.try_lock()) {
  if (blocks.empty()) {
    m_sync_lock.unlock();
    return span_pair;
  }
  block_map::const_iterator i = blocks.begin();
  if (!is_blockchain_placeholder(*i)) {
    m_sync_lock.unlock();
    return span_pair;
  }
  current_height = i->start_block_height + i->nblocks - 1;
  ++i;
  if (i == blocks.end()) {
    m_sync_lock.unlock();
    return span_pair;
  }
  first_span_height = i->start_block_height;
  if (first_span_height <= current_height + 1) {
    m_sync_lock.unlock();
    return span_pair;
  }
  MDEBUG("Found gap at start of spans: last blockchain block height " << current_height << ", first span's block height " << first_span_height);
  print();
  m_sync_lock.unlock();
  }
  span_pair.first = current_height + 1;
  span_pair.second = first_span_height - current_height - 1;
  return span_pair;
}

std::pair<uint64_t, uint64_t> block_queue::get_next_span_if_scheduled(std::list<crypto::hash> &hashes, boost::uuids::uuid &connection_id, boost::posix_time::ptime &time) const
{
  std::pair<uint64_t,uint64_t> span_pair = { 0, 0 };
  block_map::const_iterator i = blocks.begin();
  if (m_sync_lock.try_lock()) {
  if (blocks.empty()) {
    m_sync_lock.unlock();
    return span_pair;
  }
  if (is_blockchain_placeholder(*i))
    ++i;
  if (i == blocks.end()) {
    m_sync_lock.unlock();
    return span_pair;
  }
  if (!i->blocks.empty()) {
    m_sync_lock.unlock();
    return span_pair;
  }
  hashes = i->hashes;
  connection_id = i->connection_id;
  time = i->time;
  m_sync_lock.unlock();
  }
  span_pair.first = i->start_block_height;
  span_pair.second = i->nblocks;
  return span_pair;
}

void block_queue::set_span_hashes(uint64_t start_height, const boost::uuids::uuid &connection_id, std::list<crypto::hash> hashes)
{
  if (m_sync_lock.try_lock()) {
  for (block_map::iterator i = blocks.begin(); i != blocks.end(); ++i)
  {
    if (i->start_block_height == start_height && i->connection_id == connection_id)
    {
      span s = *i;
      blocks.erase(i);
      s.hashes = std::move(hashes);
      blocks.insert(s);
      m_sync_lock.unlock();
      return;
    }
  }
  }
}

bool block_queue::get_next_span(uint64_t &height, std::list<cryptonote::block_complete_entry> &bcel, boost::uuids::uuid &connection_id, bool filled) const
{
  if (m_sync_lock.try_lock()) {
  if (blocks.empty()) {
    m_sync_lock.unlock();
    return false;
  }
  block_map::const_iterator i = blocks.begin();
  if (is_blockchain_placeholder(*i))
    ++i;
  for (; i != blocks.end(); ++i)
  {
    if (!filled || !i->blocks.empty())
    {
      height = i->start_block_height;
      bcel = i->blocks;
      connection_id = i->connection_id;
      m_sync_lock.unlock();
      return true;
    }
  }
  m_sync_lock.unlock();
  }
  return false;
}

bool block_queue::has_next_span(const boost::uuids::uuid &connection_id, bool &filled) const
{
  if (m_sync_lock.try_lock()) {
  if (blocks.empty()) {
    m_sync_lock.unlock();
    return false;
  }
  block_map::const_iterator i = blocks.begin();
  if (is_blockchain_placeholder(*i))
    ++i;
  if (i == blocks.end()) {
    m_sync_lock.unlock();
    return false;
  }
  if (i->connection_id != connection_id) {
    m_sync_lock.unlock();
    return false;
  }
  filled = !i->blocks.empty();
  m_sync_lock.unlock();
  }
  return true;
}

size_t block_queue::get_data_size() const
{
  size_t size = 0;
  if (m_sync_lock.try_lock()) {
  for (const auto &span: blocks)
    size += span.size;
  m_sync_lock.unlock();
  }
  return size;
}

size_t block_queue::get_num_filled_spans_prefix() const
{
  size_t size = 0;
  if (m_sync_lock.try_lock()) {

  if (blocks.empty()) {
    m_sync_lock.unlock();
    return size;
  }
  block_map::const_iterator i = blocks.begin();
  if (is_blockchain_placeholder(*i))
    ++i;
  while (i != blocks.end() && !i->blocks.empty())
  {
    ++i;
    ++size;
  }
  m_sync_lock.unlock();
  }
  return size;
}

size_t block_queue::get_num_filled_spans() const
{
  size_t size = 0;
  if (m_sync_lock.try_lock()) {
  for (const auto &span: blocks)
  if (!span.blocks.empty())
    ++size;
  m_sync_lock.unlock();
  }
  return size;
}

crypto::hash block_queue::get_last_known_hash(const boost::uuids::uuid &connection_id) const
{
  crypto::hash hash = crypto::null_hash;
  if (m_sync_lock.try_lock()) {
  uint64_t highest_height = 0;
  for (const auto &span: blocks)
  {
    if (span.connection_id != connection_id)
      continue;
    uint64_t h = span.start_block_height + span.nblocks - 1;
    if (h > highest_height && span.hashes.size() == span.nblocks)
    {
      hash = span.hashes.back();
      highest_height = h;
    }
  }
  m_sync_lock.unlock();
  }
  return hash;
}

bool block_queue::has_spans(const boost::uuids::uuid &connection_id) const
{
  for (const auto &span: blocks)
  {
    if (span.connection_id == connection_id)
      return true;
  }
  return false;
}

float block_queue::get_speed(const boost::uuids::uuid &connection_id) const
{
  float conn_rate = -1, best_rate = 0, speed = 0;
  if (m_sync_lock.try_lock()) {
  std::unordered_map<boost::uuids::uuid, float> speeds;
  for (const auto &span: blocks)
  {
    std::unordered_map<boost::uuids::uuid, float>::iterator i = speeds.find(span.connection_id);
    if (span.blocks.empty())
      continue;
    // note that the average below does not average over the whole set, but over the
    // previous pseudo average and the latest rate: this gives much more importance
    // to the latest measurements, which is fine here
    if (i == speeds.end())
      speeds.insert(std::make_pair(span.connection_id, span.rate));
    else
      i->second = (i->second + span.rate) / 2;
  }
  for (const auto &i: speeds)
  {
    if (i.first == connection_id)
      conn_rate = i.second;
    if (i.second > best_rate)
      best_rate = i.second;
  }

  if (conn_rate <= 0) {
    m_sync_lock.unlock();
    conn_rate = 0;
    return conn_rate; // not found, assume good speed
  }
  if (best_rate == 0) {
    m_sync_lock.unlock();
    return best_rate; // everything dead ? Can't happen, but let's trap anyway
  }
  if ((conn_rate >= 0) && (best_rate > 0))
    speed = conn_rate / best_rate;
  MTRACE(" Relative speed for " << connection_id << ": " << speed << " (" << conn_rate << "/" << best_rate);
  m_sync_lock.unlock();
  }
  return speed;
}

bool block_queue::foreach(std::function<bool(const span&)> f, bool include_blockchain_placeholder) const
{
  if (m_sync_lock.try_lock()) {
  block_map::const_iterator i = blocks.begin();
  if (!include_blockchain_placeholder && i != blocks.end() && is_blockchain_placeholder(*i))
    ++i;
  while (i != blocks.end()) {
    if (!f(*i++)) {
      m_sync_lock.unlock();
      return false;
    }
  }
  m_sync_lock.unlock();
  }
  return true;
}

}
