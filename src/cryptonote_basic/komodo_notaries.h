/******************************************************************************
 * Copyright © 2014-2018 The SuperNET Developers.                     *
 *                                                    *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at            *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                    *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * SuperNET software, including this file may be copied, modified, propagated *
 * or distributed except according to the terms contained in the LICENSE file *
 *                                                    *
 * Removal or modification of this copyright notice is prohibited.        *
 *                                                    *
 ******************************************************************************/

/****************************************************************************************
 * Parts of this file have been modified for compatibility with the Blur Network.
 * The copyright notice below applies to only those portions that have been changed.
 *
 * Copyright (c) 2018-2023, Blur Network
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be
 *    used to endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************************/

#ifndef KOMODO_NOTARIES_H
#define KOMODO_NOTARIES_H

#include <vector>
#include "bitcoin/bitcoin.h"
#include "cryptonote_core/cryptonote_core.h"
#include "cryptonote_protocol/cryptonote_protocol_handler.h"
#include "p2p/net_node.h"


#pragma once

struct sha256_vstate { uint64_t length; uint32_t state[8],curlen; uint8_t buf[64]; };

namespace cryptonote {
/**
 * Encode a byte sequence as a base58-encoded string.
 * pbegin and pend cannot be nullptr, unless both are.
 */
  std::string encode_base58(const unsigned char* pbegin, const unsigned char* pend);

/**
 * Encode a byte vector as a base58-encoded string
 */
  std::string encode_base58(const std::vector<unsigned char>& vch);

/**
 * Decode a base58-encoded string (psz) into a byte vector (vchRet).
 * return true if decoding is successful.
 * psz cannot be nullptr.
 */
  bool decode_base58(const char* psz, std::vector<unsigned char>& vchRet);

/**
 * Decode a base58-encoded string (str) into a byte vector (vchRet).
 * return true if decoding is successful.
 */
  bool decode_base58(const std::string& str, std::vector<unsigned char>& vchRet);

  bool get_notary_pubkeys(std::vector<std::pair<crypto::public_key,crypto::public_key>>& notary_pubkeys);
  bool get_notary_secret_viewkeys(std::vector<crypto::secret_key>& notary_viewkeys);

namespace komodo {

  char const ASSETCHAINS_SYMBOL[5] = "BLUR";

  void vcalc_sha256(uint8_t hash[256 >> 3],uint8_t *src,int32_t len);
  void vcalc_sha256(uint8_t hash[256 >> 3],uint8_t const* src,int32_t len);
  bits256 bits256_doublesha256(uint8_t *data,int32_t datalen);
  bits256 bits256_doublesha256(uint8_t const* data,int32_t datalen);

} // namespace komodo

} // namespace cryptonote
#endif
