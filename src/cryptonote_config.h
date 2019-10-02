// Copyright (c) 2018, Blur Network
// Copyright (c) 2017-2018, The NERVA Project
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

#include <stdexcept>
#include <string>
#include <boost/uuid/uuid.hpp>

uint32_t const CRYPTONOTE_DNS_TIMEOUT_MS =                       20000;

uint64_t const CRYPTONOTE_MAX_BLOCK_NUMBER =                     500000000;
uint64_t const CRYPTONOTE_MAX_BLOCK_SIZE =                       500000000;  /* block header blob limit, never used! */
uint64_t const CRYPTONOTE_MAX_TX_SIZE =                          1000000000;
uint32_t const CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER =          0;
uint32_t const CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW =            25;
uint32_t const CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW_V6 =         25;
uint32_t const CURRENT_TRANSACTION_VERSION =                     1;
uint32_t const CURRENT_BLOCK_MAJOR_VERSION =                     1;
uint32_t const CURRENT_BLOCK_MINOR_VERSION =                     1;
uint32_t const CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT =              (60*60*2);
uint32_t const CRYPTONOTE_DEFAULT_TX_SPENDABLE_AGE =            10;

uint32_t const BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW =               60;

uint32_t const CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V2 =           (60*5);
uint32_t const CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V6 =           (60*5);
uint32_t const BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V2 =            12;

// MONEY_SUPPLY - total number coins to be generated
uint64_t const MONEY_SUPPLY =                                   UINT64_C(9223300000000000000);
uint32_t const EMISSION_SPEED_FACTOR_PER_MINUTE =                (20);
uint64_t const FINAL_SUBSIDY_PER_MINUTE =                        ((uint64_t)200000000000); /* 3 * pow(10, 11) */

uint32_t const CRYPTONOTE_REWARD_BLOCKS_WINDOW =                100;
uint32_t const CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1 =    300000;
uint32_t const CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2 =    CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1;
uint32_t const CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE =          600;
uint32_t const CRYPTONOTE_DISPLAY_DECIMAL_POINT =                12;
// COIN - number of smallest units in one coin
uint64_t const COIN =                                            ((uint64_t)1000000000000); /* pow(10, 12) */

uint32_t const DEFAULT_MIXIN =                                   4;
uint32_t const DEFAULT_RINGSIZE =                                DEFAULT_MIXIN + 1;
uint64_t const DYNAMIC_FEE_PER_KB_BASE_FEE =                     ((uint64_t)400000000);
uint64_t const DYNAMIC_FEE_PER_KB_BASE_BLOCK_REWARD =            ((uint64_t)9000000000000); /* 9 * pow(10,12) */

uint32_t const DIFFICULTY_TARGET =                               60;  /* seconds */
uint32_t const DIFFICULTY_WINDOW =                               720; /* blocks */
uint32_t const DIFFICULTY_LAG =                                  15;  /* !!! */
uint32_t const DIFFICULTY_CUT =                                  60;  /* timestamps to cut after sorting */
uint32_t const DIFFICULTY_BLOCKS_COUNT =                         DIFFICULTY_WINDOW + DIFFICULTY_LAG;

uint32_t const DIFFICULTY_BLOCKS_ESTIMATE_TIMESPAN =             DIFFICULTY_TARGET; /* just alias; used by tests */
uint32_t const DIFFICULTY_WINDOW_V2 =                            17;
uint32_t const DIFFICULTY_CUT_V2 =                               6;
uint32_t const DIFFICULTY_BLOCKS_COUNT_V2 =                      DIFFICULTY_WINDOW_V2 + DIFFICULTY_CUT_V2*2;

uint32_t const DIFFICULTY_WINDOW_V3 =                            60;
uint32_t const DIFFICULTY_BLOCKS_COUNT_V3 =                      DIFFICULTY_WINDOW_V3;

uint32_t const DIFFICULTY_WINDOW_V6 =                            60;
uint32_t const DIFFICULTY_BLOCKS_COUNT_V6 =                      DIFFICULTY_WINDOW_V6 + 1;

uint32_t const DIFFICULTY_WINDOW_V11 =                            720;
uint32_t const DIFFICULTY_LAG_V11 =                               15;
uint32_t const DIFFICULTY_BLOCKS_COUNT_V11 =                      DIFFICULTY_WINDOW_V11 + DIFFICULTY_LAG_V11;
uint32_t const DIFFICULTY_CUT_V11 =                               60;

uint32_t const CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS =       1;
uint32_t const CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS_V1 =   DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

uint32_t const BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT =          10000;  /* by default, blocks ids count in synchronizing */
uint32_t const BLOCKS_SYNCHRONIZING_DEFAULT_COUNT =              20;     /* by default, blocks count in blocks downloading */

uint32_t const CRYPTONOTE_MEMPOOL_TX_LIVETIME =                    (86400*3); /* seconds, three days */
uint32_t const CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME =     604800; /* seconds, one week */

uint32_t const COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT =           1000;

uint32_t const P2P_LOCAL_WHITE_PEERLIST_LIMIT =                  1000;
uint32_t const P2P_LOCAL_GRAY_PEERLIST_LIMIT =                   5000;

uint32_t const P2P_DEFAULT_CONNECTIONS_COUNT  =                  8;
uint32_t const P2P_DEFAULT_HANDSHAKE_INTERVAL =                  60;           /* secondes */
uint32_t const P2P_DEFAULT_PACKET_MAX_SIZE =                     50000000;     /* 50000000 bytes maximum packet size */
uint32_t const P2P_DEFAULT_PEERS_IN_HANDSHAKE =                  250;
uint32_t const P2P_DEFAULT_CONNECTION_TIMEOUT =                  5000;       /* 5 seconds */
uint32_t const P2P_DEFAULT_PING_CONNECTION_TIMEOUT =             5000;       /* 2 seconds */
uint32_t const P2P_DEFAULT_INVOKE_TIMEOUT =                      120000;     /* 2 minutes */
uint32_t const P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT =            5000;       /* 5 seconds */
uint32_t const P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT =       70;
uint32_t const P2P_DEFAULT_ANCHOR_CONNECTIONS_COUNT =            2;
uint32_t const P2P_DEFAULT_LIMIT_RATE_UP =                       2048;       /*  kB/s */
uint32_t const P2P_DEFAULT_LIMIT_RATE_DOWN =                    8192;       /* kB/s */

uint32_t const P2P_FAILED_ADDR_FORGET_SECONDS =                  3600;     /* 1 hour */
uint32_t const P2P_IP_BLOCKTIME =                                (60*60*24);  /* 24 hour */
uint32_t const P2P_IP_FAILS_BEFORE_BLOCK =                       10;
uint32_t const P2P_IDLE_CONNECTION_KILL_INTERVAL =               (5*60); /* 5 minutes */

uint32_t const P2P_SUPPORT_FLAG_FLUFFY_BLOCKS =                  0x01;
uint32_t const P2P_SUPPORT_FLAGS =                               P2P_SUPPORT_FLAG_FLUFFY_BLOCKS;

std::string const CRYPTONOTE_NAME =                         "blurnetwork";
std::string const CRYPTONOTE_BLOCKCHAINDATA_FILENAME =      "data.mdb";
std::string const CRYPTONOTE_BLOCKCHAINDATA_LOCK_FILENAME = "lock.mdb";
std::string const P2P_NET_DATA_FILENAME =                   "peers_state.bin";
std::string const MINER_CONFIG_FILE_NAME =                  "miner_conf.json";

#define THREAD_STACK_SIZE                       0x80000

uint32_t const PER_KB_FEE_QUANTIZATION_DECIMALS =        8;

uint32_t const HASH_OF_HASHES_STEP =                     256;

uint64_t const DEFAULT_TXPOOL_MAX_SIZE =                 648000000ULL; /* 3 days at 300000, in bytes */

// New constants are intended to go here
namespace config
{
  uint64_t const DEFAULT_DUST_THRESHOLD = 0; /* deprecated */

  uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 7757; /* bL */
  uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 15654; /* uR */
  uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 8597; /* Ry */
  uint32_t const P2P_DEFAULT_PORT = 52541;
  uint32_t const RPC_DEFAULT_PORT = 52542;
  boost::uuids::uuid const NETWORK_ID = { {
      0x1E,0x32, 0x11, 0x2F , 0x54, 0x86 , 0x37, 0xFF, 0xAB, 0x89, 0x01, 0x92, 0xAA, 0xBC, 0x2F, 0x2D
    } };
  std::string const GENESIS_TX = "011901ff0001ffffffffffff0102bca7c97f7074ea888eac572fda0964cc864baf7bc07d6cecc052728039009d7621017133140c2abc1825f8d411db7bee4379a2a0f21b7af60e44ed7f07e9e66ccd8800";


  uint32_t const GENESIS_NONCE = 10000;

  namespace testnet
  {
  uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 2124; /* b8 */
  uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 3462; /* Ps */
  uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 2195; // Rb
    uint32_t const P2P_DEFAULT_PORT = 11111;
    uint32_t const RPC_DEFAULT_PORT = 21111;
    boost::uuids::uuid const NETWORK_ID = { {
        0x22 ,0x36, 0xF1, 0x22 , 0x54, 0x86 , 0x37, 0xFF, 0xAB, 0x89, 0x01, 0x92, 0xAA, 0xBC, 0x2F, 0x16
      } };
  }

  namespace stagenet
  {
  uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 5622; /* Bi */
  uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 2122; /* ao */
  uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 134; /* Ry */
    uint32_t const P2P_DEFAULT_PORT = 31105;
    uint32_t const RPC_DEFAULT_PORT = 31106;
    boost::uuids::uuid const NETWORK_ID = { {
        0x22 ,0x36, 0xF1, 0x22 , 0x54, 0x86 , 0x36, 0xFF, 0xAB, 0x51, 0x00, 0x4F, 0x3C, 0x3D, 0xAA, 0x17
      } };
  }
}



namespace cryptonote
{
  enum network_type : uint8_t
  {
    MAINNET = 0,
    TESTNET = 0xF,
    STAGENET = 0x7F,
    FAKECHAIN = 0x80,
    UNDEFINED = 254
  };
  struct config_t
  {
    uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX;
    uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX;
    uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX;
    uint32_t const P2P_DEFAULT_PORT;
    uint32_t const RPC_DEFAULT_PORT;
    boost::uuids::uuid const NETWORK_ID;
    std::string const GENESIS_TX;
    uint32_t const GENESIS_NONCE;
  };
  inline const config_t& get_config(network_type nettype)
  {
    static const config_t mainnet = {
      ::config::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::P2P_DEFAULT_PORT,
      ::config::RPC_DEFAULT_PORT,
      ::config::NETWORK_ID,
      ::config::GENESIS_TX,
      ::config::GENESIS_NONCE
    };
    static const config_t testnet = {
      ::config::testnet::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::testnet::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::testnet::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::testnet::P2P_DEFAULT_PORT,
      ::config::testnet::RPC_DEFAULT_PORT,
      ::config::testnet::NETWORK_ID,
    };
    static const config_t stagenet = {
      ::config::stagenet::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::stagenet::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::stagenet::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::stagenet::P2P_DEFAULT_PORT,
      ::config::stagenet::RPC_DEFAULT_PORT,
      ::config::stagenet::NETWORK_ID,
    };
    switch (nettype)
    {
      case MAINNET: return mainnet;
      case TESTNET: return testnet;
      case STAGENET: return stagenet;
      case FAKECHAIN: return mainnet;
      default: throw std::runtime_error("Invalid network type");
    }
  };
}
