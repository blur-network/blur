// Copyright (c) 2019-2021, Blur Network
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

#include "span.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "scoped_message_writer.h"

  std::string bytes256_to_hex(std::vector<uint8_t> &input)
  {
    static const char characters[] = "0123456789abcdef";
    std::string ret(input.size() * 2, 0);
    char *buffer = const_cast<char *>(ret.data());

    size_t elements = input.size();
    bool too_long = (elements > 32);
    std::string short_long = too_long ? ("longer") : ("shorter");

    if (elements != 32) {
      MERROR("Tried to convert a 256-bit vector that is " << short_long << " than the required 32-byte length.");
      return "";
    }

    for (const auto &each_byte : input) {
      *buffer++ = characters[each_byte >> 4];
      *buffer++ = characters[each_byte & 0x0F];
    }
    return ret;
  }
  //----------------------------------------------------------------
  std::vector<uint8_t> hex_to_bytes256(const std::string &input)
  {
    size_t len = input.length();
    bool too_long = (len > 64);
    std::string short_long = too_long ? ("longer") : ("shorter");
    std::vector<uint8_t> out;

    if (len != 64) {
      MERROR("Tried to convert a hex string that is " << short_long << " than the required 64-character length.");
      std::fill(out.begin(), out.begin()+32, 0);
      return out;
    }

    for(size_t i = 0; i < len; i += 2) {
      std::istringstream strm(input.substr(i, 2));
      uint8_t x;
      strm >> std::hex >> x;
      out.push_back(x);
    }
    return out;
  }
  //----------------------------------------------------------------
  std::string span_to_hex(epee::span<const uint8_t> &input)
  {
    static const char characters[] = "0123456789abcdef";
    std::string ret(input.size() * 2, 0);
    char *buffer = const_cast<char *>(ret.data());

    size_t elements = input.size();
    bool too_long = (elements > 32);
    std::string short_long = too_long ? ("longer") : ("shorter");

    if (elements != 32) {
      MERROR("Tried to convert a 256-bit vector that is " << short_long << " than the required 32-byte length.");
      return "";
    }

    for (const auto &each_byte : input) {
      *buffer++ = characters[each_byte >> 4];
      *buffer++ = characters[each_byte & 0x0F];
    }
    return ret;
  }
  //----------------------------------------------------------------
  std::vector<uint8_t> hex_to_bytes4096(const std::string &input)
  {
    size_t len = input.length();
    bool too_long = (len > 4096);
    std::string short_long = too_long ? ("longer") : ("shorter");
    std::vector<uint8_t> out;

    if (len != 64) {
      MERROR("Tried to convert a hex string that is " << short_long << " than the required 4096-character length.");
      std::fill(out.begin(), out.begin()+4096, 0);
      return out;
    }

    for(size_t i = 0; i < len; i += 2) {
      std::istringstream strm(input.substr(i, 2));
      uint8_t x;
      strm >> std::hex >> x;
      out.push_back(x);
    }
    return out;
  }
