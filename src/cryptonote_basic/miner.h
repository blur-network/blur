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

#pragma once 

#include <boost/program_options.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <boost/thread/thread.hpp>
#include <atomic>
#include "cryptonote_basic.h"
#include "difficulty.h"
#include "math_helper.h"
#ifdef _WIN32
#include <windows.h>
#elif defined(__linux__)
#include <unistd.h>
#include <sys/resource.h>
#include <sys/times.h>
#include <time.h>
#endif

using namespace boost::this_thread;

class thread_group
{
public:
    thread_group(const thread_group&) = delete;
    thread_group& operator=(const thread_group&) = delete;

    thread_group();
    ~thread_group();

    template<typename F>
    boost::thread* create_thread(F threadfunc);
    void add_thread(boost::thread* thrd);
    void remove_thread(boost::thread* thrd);
    bool is_this_thread_in();
    bool is_thread_in(boost::thread* thrd);
    void join_all();
    void interrupt_all();
    int size() const;
};

namespace cryptonote
{
  template<class T, class Tt>
  T get_index(T i, Tt j) {
    std::string I = std::to_string(i);
    decltype(i) s;
    s = j[i];
    return s;
  }

  struct i_miner_handler
  {
    virtual bool handle_block_found(block& b) = 0;
    virtual bool get_block_template(block& b, const account_public_address& adr, difficulty_type& diffic, uint64_t& height, uint64_t& expected_reward, const blobdata& ex_nonce) = 0;
  protected:
    ~i_miner_handler(){};
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  class thread_counter
  {
    friend class miner;
    public:
     thread_counter() : m_thread_count(0) { }

     uint32_t* add(uint32_t val)
     {
       boost::recursive_mutex::scoped_lock m_threads_count_lock(m_threads_mutex);
       m_thread_count += val;
       return &m_thread_count;
     }

       uint32_t increment() {
         boost::recursive_mutex::scoped_lock m_threads_count_lock(m_threads_mutex);
         const uint32_t* post = add(1);
         thread_indices.push_back(*post);
         return *post;
       }

       uint32_t check() {
         return m_thread_count;
       }

     private:
       boost::recursive_mutex m_threads_mutex;
       std::vector<uint32_t> thread_indices;
       thread_group threads;
       uint32_t m_thread_count;
   };


  class miner : public thread_counter
  {
  public:
    miner(i_miner_handler* phandler);
    ~miner();
    bool init(const boost::program_options::variables_map& vm, network_type nettype);
    static void init_options(boost::program_options::options_description& desc);
    bool set_block_template(block const& bl, difficulty_type const& diffic, uint64_t const& height);
    bool on_block_chain_update();
    bool start(const account_public_address& adr, uint32_t const& threads_count);
    uint64_t get_speed() const;
    virtual uint32_t get_thread_count() { return thread_count.check(); };
    void send_stop_signal();
    bool stop();
    bool is_mining() const;
    const account_public_address& get_mining_address() const;
    bool on_idle();
    void on_synchronized();
    //synchronous analog (for fast calls)
    bool find_nonce_for_given_block(block& bl, difficulty_type const& diffic, uint64_t const& height);
    void pause();
    void resume();
    void do_print_hashrate(bool do_hr);

  private:
    thread_counter thread_count;
    bool worker_thread();
    bool request_block_template();
    void  merge_hr();

    struct miner_config
    {
      uint64_t current_extra_message_index;

      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(current_extra_message_index)
      END_KV_SERIALIZE_MAP()
    };

    std::list<uint32_t> m_threads;
    volatile uint32_t m_stop;
    epee::critical_section m_template_lock;
    block m_template;
    std::atomic<uint32_t> m_template_no;
    std::atomic<uint32_t> m_starter_nonce;
    difficulty_type m_diffic;
    uint64_t m_height;
    std::atomic<uint32_t> m_thread_index;
    virtual std::vector<uint32_t> get_thread_indices() { return thread_count.thread_indices; };
    std::atomic<uint32_t> m_threads_total;
    std::atomic<int32_t> m_pausers_count;

    i_miner_handler* m_phandler;
    account_public_address m_mine_address;
    epee::math_helper::once_a_time_seconds<5> m_update_block_template_interval;
    epee::math_helper::once_a_time_seconds<2> m_update_merge_hr_interval;
    std::vector<blobdata> m_extra_messages;
    miner_config m_config;
    std::string m_config_folder_path;
    std::atomic<uint64_t> m_last_hr_merge_time;
    std::atomic<uint64_t> m_hashes;
    std::atomic<uint64_t> m_current_hash_rate;
    epee::critical_section m_last_hash_rates_lock;
    std::list<uint64_t> m_last_hash_rates;
    bool m_do_print_hashrate;
    bool m_do_mining;
    void miner_thread();
  };
}
