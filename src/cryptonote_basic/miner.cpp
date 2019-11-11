// Copyright (c) 2018-2019, Blur Network
// Copyright (c) 2014-2018, The Monero Project
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

#include <sstream>
#include <numeric>
#include <boost/utility/value_init.hpp>
#include <boost/interprocess/detail/atomic.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/limits.hpp>
#include <boost/thread.hpp>
#include "include_base_utils.h"
#include "misc_language.h"
#include "syncobj.h"
#include "cryptonote_basic_impl.h"
#include "cryptonote_format_utils.h"
#include "file_io_utils.h"
#include "common/command_line.h"
#include "string_coding.h"
#include "string_tools.h"
#include "storages/portable_storage_template_helper.h"
#include "boost/logic/tribool.hpp"

#ifdef __APPLE__
  #include <sys/times.h>
  #include <IOKit/IOKitLib.h>
  #include <IOKit/ps/IOPSKeys.h>
  #include <IOKit/ps/IOPowerSources.h>
  #include <mach/mach_host.h>
  #include <AvailabilityMacros.h>
  #include <TargetConditionals.h>
#endif

#ifdef __FreeBSD__
#include <devstat.h>
#include <errno.h>
#include <fcntl.h>
#include <machine/apm_bios.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/sysctl.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include <functional>

#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "miner"

using namespace epee;

#include "miner.h"


extern "C" void slow_hash_allocate_state();
extern "C" void slow_hash_free_state();
namespace cryptonote
{
  class thread_counter;
  thread_counter thread_count;

  uint32_t* thread_counter::add(uint32_t val)
  {
    boost::recursive_mutex::scoped_lock m_threads_count_lock(m_threads_mutex);
    m_thread_count += val;
    return &m_thread_count;
  }

       uint32_t thread_counter::increment() {
         boost::recursive_mutex::scoped_lock m_threads_count_lock(m_threads_mutex);
         const uint32_t* post = add(1);
         thread_indices.push_back(*post);
         return *post;
       }

       uint32_t thread_counter::check() {
         return m_thread_count;
       }


  namespace
  {
    const command_line::arg_descriptor<std::string> arg_extra_messages =  {"extra-messages-file", "Specify file for extra messages to include into coinbase transactions", "", true};
    const command_line::arg_descriptor<std::string> arg_start_mining =    {"start-mining", "Specify wallet address to mining for", "", true};
    const command_line::arg_descriptor<uint32_t>      arg_mining_threads =  {"mining-threads", "Specify mining threads count", 0, true};
  }

  miner::miner(i_miner_handler* phandler):m_stop(1),
    m_template(boost::value_initialized<block>()),
    m_template_no(0),
    m_diffic(0),
    m_thread_index(0),
    m_phandler(phandler),
    m_height(0),
    m_pausers_count(0),
    m_threads_total(0),
    m_starter_nonce(0),
    m_last_hr_merge_time(0),
    m_hashes(0),
    m_do_print_hashrate(false),
    m_do_mining(false),
    m_current_hash_rate(0)
  {
  }
  //-----------------------------------------------------------------------------------------------------
  miner::~miner()
  {
    stop();
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::set_block_template(block const& bl, difficulty_type const& di, uint64_t const& height)
  {
    CRITICAL_REGION_LOCAL(m_template_lock);
    m_template = bl;
    m_diffic = di;
    m_height = height;
    ++m_template_no;
    m_starter_nonce = crypto::rand<uint32_t>();
    return true;
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::on_block_chain_update()
  {
    if(!is_mining())
      return true;

    return request_block_template();
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::request_block_template()
  {
    block bl = AUTO_VAL_INIT(bl);
    difficulty_type di = 1;
    uint64_t height = 1;
    uint64_t expected_reward; //only used for RPC calls - could possibly be useful here too?

    cryptonote::blobdata extra_nonce;
    if(m_extra_messages.size() && m_config.current_extra_message_index < m_extra_messages.size())
    {
      extra_nonce = m_extra_messages[m_config.current_extra_message_index];
    }

    if(!m_phandler->get_block_template(bl, m_mine_address, di, height, expected_reward, extra_nonce))
    {
      LOG_ERROR("Failed to get_block_template(), stopping mining");
      return false;
    }
    set_block_template(bl, di, height);
    return true;
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::on_idle()
  {
    m_update_block_template_interval.do_call([&](){
      if(is_mining())request_block_template();
      return true;
    });

    m_update_merge_hr_interval.do_call([&](){
      merge_hr();
      return true;
    });

    return true;
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::do_print_hashrate(bool do_hr)
  {
    m_do_print_hashrate = do_hr;
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::merge_hr()
  {
    if(m_last_hr_merge_time && is_mining())
    {
      m_current_hash_rate = m_hashes * 1000 / ((misc_utils::get_tick_count() - m_last_hr_merge_time + 1));
      CRITICAL_REGION_LOCAL(m_last_hash_rates_lock);
      m_last_hash_rates.push_back(m_current_hash_rate);
      if(m_last_hash_rates.size() > 19)
        m_last_hash_rates.pop_front();
      if(m_do_print_hashrate)
      {
        uint64_t total_hr = std::accumulate(m_last_hash_rates.begin(), m_last_hash_rates.end(), 0);
        float hr = static_cast<float>(total_hr)/static_cast<float>(m_last_hash_rates.size());
        const auto flags = std::cout.flags();
        const auto precision = std::cout.precision();
        std::cout << "hashrate: " << std::setprecision(4) << std::fixed << hr << flags << precision << ENDL;
      }
    }
    m_last_hr_merge_time = misc_utils::get_tick_count();
    m_hashes = 0;
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::init_options(boost::program_options::options_description& desc)
  {
    command_line::add_arg(desc, arg_extra_messages);
    command_line::add_arg(desc, arg_start_mining);
    command_line::add_arg(desc, arg_mining_threads);
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::miner_thread()
  {
    LOG_PRINT_L1("Miner thread [" << std::to_string(thread_count.increment()) << "] started!" << std::endl);
    uint32_t nonce = miner::m_starter_nonce + thread_count.check();
    uint64_t height = 0;
    difficulty_type local_diff = 0;
    uint32_t local_template_ver = 0;
    block b;
    slow_hash_allocate_state();
    while(!m_stop)
    {

      if(local_template_ver != m_template_no)
      {
        CRITICAL_REGION_BEGIN(m_template_lock);
        b = m_template;
        local_diff = m_diffic;
        height = m_height;
        nonce = miner::m_starter_nonce + thread_count.check();
        local_template_ver = m_template_no;
        CRITICAL_REGION_END();
      }

      b.nonce = nonce;
      crypto::hash h;
      get_block_longhash(b, h, height);

      if(check_hash(h, local_diff))
      {
        //we lucky!
        ++miner::m_config.current_extra_message_index;
        MGINFO_GREEN("Found block " << get_block_hash(b) << " at height " << height << " for difficulty: " << local_diff);
        if(!m_phandler->handle_block_found(b))
        {
          --m_config.current_extra_message_index;
          if (!m_config_folder_path.empty())
            epee::serialization::store_t_to_json_file(m_config, m_config_folder_path + "/" + MINER_CONFIG_FILE_NAME);
        }
      }
      nonce+=miner::m_threads_total;
      ++miner::m_hashes;
    }
    slow_hash_free_state();
    MGINFO("Miner thread stopped ["<< thread_count.check() << "]");
    return;
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::init(const boost::program_options::variables_map& vm, network_type nettype)
  {
    if(command_line::has_arg(vm, arg_extra_messages))
    {
      std::string buff;
      bool r = file_io_utils::load_file_to_string(command_line::get_arg(vm, arg_extra_messages), buff);
      CHECK_AND_ASSERT_MES(r, false, "Failed to load file with extra messages: " << command_line::get_arg(vm, arg_extra_messages));
      std::vector<std::string> extra_vec;
      boost::split(extra_vec, buff, boost::is_any_of("\n"), boost::token_compress_on );
      m_extra_messages.resize(extra_vec.size());
      for(size_t i = 0; i != extra_vec.size(); i++)
      {
        string_tools::trim(extra_vec[i]);
        if(!extra_vec[i].size())
          continue;
        std::string buff = string_encoding::base64_decode(extra_vec[i]);
        if(buff != "0")
          m_extra_messages[i] = buff;
      }
      m_config_folder_path = boost::filesystem::path(command_line::get_arg(vm, arg_extra_messages)).parent_path().string();
      m_config = AUTO_VAL_INIT(m_config);
      const std::string filename = m_config_folder_path + "/" + MINER_CONFIG_FILE_NAME;
      CHECK_AND_ASSERT_MES(epee::serialization::load_t_from_json_file(m_config, filename), false, "Failed to load data from " << filename);
      MINFO("Loaded " << m_extra_messages.size() << " extra messages, current index " << m_config.current_extra_message_index);
    }

    if(command_line::has_arg(vm, arg_start_mining))
    {
      address_parse_info info;
      if(!cryptonote::get_account_address_from_str(info, nettype, command_line::get_arg(vm, arg_start_mining)) || info.is_subaddress)
      {
        LOG_ERROR("Target account address " << command_line::get_arg(vm, arg_start_mining) << " has wrong format, starting daemon canceled");
        return false;
      } else {
        m_mine_address = info.address;
        m_threads_total = thread_count.increment();
        m_do_mining = true;
        if(command_line::has_arg(vm, arg_mining_threads))
        {
          for (uint32_t i = 0; i < (command_line::get_arg(vm, arg_mining_threads)); ++i) {
             threads.create_thread(boost::bind(&miner::miner_thread, this));
             m_threads_total = i;
          }
        }
      }
    }

    return true;
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::is_mining() const
  {
    return !m_stop;
  }
  //-----------------------------------------------------------------------------------------------------
  const account_public_address& miner::get_mining_address() const
  {
    return m_mine_address;
  }
  //-----------------------------------------------------------------------------------------------------
/*  uint32_t miner::get_thread_count() {
    return thread_count.check();
  }*/
  //-----------------------------------------------------------------------------------------------------
  bool miner::start(const account_public_address& adr, uint32_t const& threads_count)
  {
    m_mine_address = adr;
    if (get_thread_count() > 0) {
      MWARNING("Mining already started with thread count = " << std::to_string(get_thread_count()) << ". Continuing with this count! If you wish to add more threads, stop mining first!");
      m_threads_total = get_thread_count();
      return true;
    } else {
      for (size_t i = 0; i < threads_count; i++) {
        m_threads_total = thread_count.increment();
        threads.create_thread(boost::bind(&miner::miner_thread, this));
      }
    }
    m_starter_nonce = crypto::rand<uint32_t>();
    if(is_mining())
    {
      LOG_ERROR("Starting miner but it's already started");
      return false;
    }

    request_block_template();//lets update block template

    boost::interprocess::ipcdetail::atomic_write32(&m_stop, 0);
    LOG_PRINT_L0("Mining has started with " << threads_count << " threads, good luck!" );

    return true;
  }
  //-----------------------------------------------------------------------------------------------------
  uint64_t miner::get_speed() const
  {
    if(is_mining()) {
      return m_current_hash_rate;
    }
    else {
      return 0;
    }
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::send_stop_signal()
  {
    boost::interprocess::ipcdetail::atomic_write32(&m_stop, 1);
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::stop()
  {
    MTRACE("Miner has received stop signal");
    threads.join_all();
    if (!is_mining())
    {
      MDEBUG("Not mining - nothing to stop" );
      return true;
    }

    send_stop_signal();
    //CRITICAL_REGION_LOCAL(m_threads_lock);

    MINFO("Mining has been stopped, " << m_threads.size() << " finished" );
    m_threads.clear();
    return true;
  }
  //-----------------------------------------------------------------------------------------------------
  bool miner::find_nonce_for_given_block(block& bl, const difficulty_type& diffic, uint64_t const& height)
  {
    for(; bl.nonce != std::numeric_limits<uint32_t>::max(); bl.nonce++)
    {
      crypto::hash h;
      get_block_longhash(bl, h, height);

      if(check_hash(h, diffic))
      {
        bl.invalidate_hashes();
        return true;
      }
    }
    bl.invalidate_hashes();
    return false;
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::on_synchronized()
  {
    if(m_do_mining)
    {
      boost::thread::attributes attrs;
      attrs.set_stack_size(THREAD_STACK_SIZE);

      start(m_mine_address, m_threads_total);
    }
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::pause()
  {
    MDEBUG("miner::pause: " << m_pausers_count << " -> " << (m_pausers_count + 1));
    ++m_pausers_count;
    if(m_pausers_count == 1 && is_mining())
      MDEBUG("MINING PAUSED");
  }
  //-----------------------------------------------------------------------------------------------------
  void miner::resume()
  {
    MDEBUG("miner::resume: " << m_pausers_count << " -> " << (m_pausers_count - 1));
    --m_pausers_count;
    if(m_pausers_count < 0)
    {
      m_pausers_count = 0;
      MERROR("Unexpected miner::resume() called");
    }
    if(!m_pausers_count && is_mining())
      MDEBUG("MINING RESUMED");
  }
  //-----------------------------------------------------------------------------------------------------
}
