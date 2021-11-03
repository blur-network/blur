// Copyright (c) 2018-2022, Blur Network
// Copyright (c) 2014-2018, The Monero Project
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

extern "C" {

#pragma once

#pragma pack(push, 1)
struct output_data_t
{
  crypto::public_key pubkey;
  uint64_t           unlock_time;
  uint64_t           height;
  rct::key           commitment;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct tx_data_t
{
  uint64_t tx_id;
  uint64_t unlock_time;
  uint64_t block_id;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct btc_data_t
{
  uint64_t btc_idx;
  crypto::hash blk_hash;
};
#pragma pack(pop)

namespace cryptonote {

typedef struct mdb_block_info
{
  uint64_t bi_height;
  uint64_t bi_timestamp;
  uint64_t bi_coins;
  uint64_t bi_size; // a size_t really but we need 32-bit compat
  difficulty_type bi_diff;
  crypto::hash bi_hash;
} mdb_block_info;

typedef struct blk_height {
    crypto::hash bh_hash;
    uint64_t bh_height;
} blk_height;

typedef struct btcindex {
    crypto::hash key;
    btc_data_t data;
} btc_index;

typedef struct txindex {
    crypto::hash key;
    tx_data_t data;
} txindex;

typedef struct outkey {
    uint64_t amount_index;
    uint64_t output_id;
    output_data_t data;
} outkey;

typedef struct outtx {
    uint64_t output_id;
    crypto::hash tx_hash;
    uint64_t local_index;
} outtx;

} //namespace cryptonote

}
