// Copyright (c) 2018-2023, Blur Network
// Copyright (c) 2017-2018, The Masari Project
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


#include "checkpoints.h"

#include "misc_log_ex.h"
#include "string_tools.h"
#include "storages/portable_storage_template_helper.h" // epee json include
#include "serialization/keyvalue_serialization.h"

#undef MONERO_DEFAULT_LOG_CATEGORY
#define MONERO_DEFAULT_LOG_CATEGORY "checkpoints"

namespace cryptonote
{
  /**
   * @brief struct for loading a checkpoint from json
   */
  struct t_hashline
  {
    uint64_t height; //!< the height of the checkpoint
    std::string hash; //!< the hash for the checkpoint
        BEGIN_KV_SERIALIZE_MAP()
          KV_SERIALIZE(height)
          KV_SERIALIZE(hash)
        END_KV_SERIALIZE_MAP()
  };

  /**
   * @brief struct for loading many checkpoints from json
   */
  struct t_hash_json {
    std::vector<t_hashline> hashlines; //!< the checkpoint lines from the file
        BEGIN_KV_SERIALIZE_MAP()
          KV_SERIALIZE(hashlines)
        END_KV_SERIALIZE_MAP()
  };

  //---------------------------------------------------------------------------
  checkpoints::checkpoints()
  {
  }
  //---------------------------------------------------------------------------
  bool checkpoints::add_checkpoint(uint64_t height, const std::string& hash_str)
  {
    crypto::hash h = crypto::null_hash;
    bool r = epee::string_tools::parse_tpod_from_hex_string(hash_str, h);
    CHECK_AND_ASSERT_MES(r, false, "Failed to parse checkpoint hash string into binary representation!");

    // return false if adding at a height we already have AND the hash is different
    if (m_points.count(height))
    {
      CHECK_AND_ASSERT_MES(h == m_points[height], false, "Checkpoint at given height already exists, and hash for new checkpoint was different!");
    }
    m_points[height] = h;
    return true;
  }
  //---------------------------------------------------------------------------
  bool checkpoints::is_in_checkpoint_zone(uint64_t height) const
  {
    return !m_points.empty() && (height <= (--m_points.end())->first);
  }
  //---------------------------------------------------------------------------
  bool checkpoints::check_block(uint64_t height, const crypto::hash& h, bool& is_a_checkpoint) const
  {
    auto it = m_points.find(height);
    is_a_checkpoint = it != m_points.end();
    if(!is_a_checkpoint)
      return true;

    if(it->second == h)
    {
      MINFO("CHECKPOINT PASSED FOR HEIGHT " << height << " " << h);
      return true;
    }else
    {
      MWARNING("CHECKPOINT FAILED FOR HEIGHT " << height << ". EXPECTED HASH: " << it->second << ", FETCHED HASH: " << h);
      return false;
    }
  }
  //---------------------------------------------------------------------------
  bool checkpoints::check_block(uint64_t height, const crypto::hash& h) const
  {
    bool ignored;
    return check_block(height, h, ignored);
  }
  //---------------------------------------------------------------------------
  //FIXME: is this the desired behavior?
  bool checkpoints::is_alternative_block_allowed(uint64_t blockchain_height, uint64_t block_height) const
  {
    if (0 == block_height)
      return false;

    auto it = m_points.upper_bound(blockchain_height);
    // Is blockchain_height before the first checkpoint?
    if (it == m_points.begin())
      return true;

    --it;
    uint64_t checkpoint_height = it->first;
    return checkpoint_height < block_height;
  }
  //---------------------------------------------------------------------------
  uint64_t checkpoints::get_max_height() const
  {
    std::map< uint64_t, crypto::hash >::const_iterator highest =
        std::max_element( m_points.begin(), m_points.end(),
                         ( boost::bind(&std::map< uint64_t, crypto::hash >::value_type::first, _1) <
                           boost::bind(&std::map< uint64_t, crypto::hash >::value_type::first, _2 ) ) );
    return highest->first;
  }
  //---------------------------------------------------------------------------
  const std::map<uint64_t, crypto::hash>& checkpoints::get_points() const
  {
    return m_points;
  }

  bool checkpoints::check_for_conflicts(const checkpoints& other) const
  {
    for (auto& pt : other.get_points())
    {
      if (m_points.count(pt.first))
      {
        CHECK_AND_ASSERT_MES(pt.second == m_points.at(pt.first), false, "Checkpoint at given height already exists, and hash for new checkpoint was different!");
      }
    }
    return true;
  }

  bool checkpoints::init_default_checkpoints(network_type nettype)
  {
    if (nettype == TESTNET)
    {
      return true;
    }
    if (nettype == STAGENET)
    {
      return true;
    }
    ADD_CHECKPOINT(1,       "dded291f5d83d0fcce15ed07a12b0f12a5a328d319eecf91f327fbe81a629a6e");
    ADD_CHECKPOINT(10,       "c9caaca89a64182a58f34275e9b3204c04497f26a9da04ac9c36e32df959b5a6");
    ADD_CHECKPOINT(100,      "0c94df478c3ce73d37082a432349aa576ed36bb07ff55c066dadfcda73d53a6f");
    ADD_CHECKPOINT(1000,     "cfed96d69e197895908b71766fcb4f1887ecb20da5a199ca544003a1fb6e751a");
    ADD_CHECKPOINT(10000,    "f6c045bc8f4e4749185c58b1673e0ba1c0256b7c5b0bc4c11e5b6563b45193ab");
    ADD_CHECKPOINT(50000,    "655124b25dc172446ca4edccf6bdfb1e6b6aadf4f7fb543b6409ab890f5e7f7d");
    ADD_CHECKPOINT(80000,    "250106eea9561c099cab09db3ec1a8967beba2b02fe2e99d2206dbb80b17b7b7");
    ADD_CHECKPOINT(100000,   "6e45258946faa11868f183e8f289511b9e2c266320de66d221b1ed5b014cee47");
    ADD_CHECKPOINT(150000,   "88210b6d446d4f4c5a0a77432e8a2f1d5da0fd3fc82ef30b8db3693208e8fefe");
    ADD_CHECKPOINT(185000,   "96ddfcdd4be315e438a93bd82cd505235f96ff33349313357ca123937f5c4fe1");
    ADD_CHECKPOINT(200000,   "d6f939964ad727a7bd2bb44a909bf02079ea9caf7f55b0e791338860b3a89d0d");
    ADD_CHECKPOINT(250000,   "4dadcf431bc2ac3360c26e9793f2a87c6c466480d7039090638e6f81ef02fbd2");
    ADD_CHECKPOINT(265000,   "a3cad8c2435436ef94d0452757d1a51becca8e645ab90ba40b89fd643f951601");
    ADD_CHECKPOINT(342000,   "45215587f694008a45f9b1b182999a340a444a6339f414150295d411738668f0");
    ADD_CHECKPOINT(400000,   "187fc1cb47997992a720ac2363c41011ade39b7030003b55faabf8da86c9ac88");
    ADD_CHECKPOINT(500000,   "604b1c1e850ff5f2904525dcfa701e03d6a6bd700496f4d95f351344bbb6e753");
    ADD_CHECKPOINT(600000,   "e6b72b35626d2356607c02cb6cecb889c885a35af8bfb78c4362c39f251fe378");
    ADD_CHECKPOINT(700000,   "941b0c83ef8a437d6e14eefb6e83a1df4b2281193041bfffbed59488ad369e93");
    ADD_CHECKPOINT(800000,   "e48803e4b699e5c3ac6f984bf1ae01a84f4bb88f2c1470104669fc0c91401e2f");
    ADD_CHECKPOINT(900000,   "5836ef22a883cfd41202b66c8609a3561fa800bcf36ff1cb6b144bb3800f0753");
    ADD_CHECKPOINT(1000000,  "346e0806c1e2e2ba014d230d5750aa660be5456c9a3e60fd21927c5589ede311");
    ADD_CHECKPOINT(1100000,  "a80135dc92696f1ab373e71c0fe99b81decef74a352ea26258b80879c5af8596");
    ADD_CHECKPOINT(1500000,  "ee4dcb130a0e934d64665d3b45b58835275b1f57e2f3a0a5bbf2b967363d3b98");
    ADD_CHECKPOINT(2000000,  "65b40b85f7341e919dd2904092eefa21605adfdb14f8245b2aaf231293c5ebad");
    ADD_CHECKPOINT(2400000,  "06c55083a74a733651f64f1ce9178294153e9790002be37b46be040abc84ebd2");
    return true;
  }

  bool checkpoints::load_checkpoints_from_json(const std::string &json_hashfile_fullpath)
  {
    boost::system::error_code errcode;
    if (! (boost::filesystem::exists(json_hashfile_fullpath, errcode)))
    {
      LOG_PRINT_L1("Blockchain checkpoints file not found");
      return true;
    }

    LOG_PRINT_L1("Adding checkpoints from blockchain hashfile");

    uint64_t prev_max_height = get_max_height();
    LOG_PRINT_L1("Hard-coded max checkpoint height is " << prev_max_height);
    t_hash_json hashes;
    if (!epee::serialization::load_t_from_json_file(hashes, json_hashfile_fullpath))
    {
      MERROR("Error loading checkpoints from " << json_hashfile_fullpath);
      return false;
    }
    for (std::vector<t_hashline>::const_iterator it = hashes.hashlines.begin(); it != hashes.hashlines.end(); )
    {
      uint64_t height;
      height = it->height;
      if (height <= prev_max_height) {
	LOG_PRINT_L1("ignoring checkpoint height " << height);
      } else {
	std::string blockhash = it->hash;
	LOG_PRINT_L1("Adding checkpoint height " << height << ", hash=" << blockhash);
	ADD_CHECKPOINT(height, blockhash);
      }
      ++it;
    }

    return true;
  }

  bool checkpoints::load_new_checkpoints(const std::string &json_hashfile_fullpath, network_type nettype)
  {
    bool result;

    result = load_checkpoints_from_json(json_hashfile_fullpath);

    return result;
  }
}
