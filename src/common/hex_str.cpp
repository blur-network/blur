#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "scoped_message_writer.h"


  std::string bytes256_to_hex(const std::vector<uint8_t> &input)
  {
    static const char characters[] = "0123456789abcdef";
    std::string ret(input.size() * 2, 0);
    char *buffer = const_cast<char *>(ret.data());

    size_t elements = input.size();
    bool too_long = (elements > 32) ? 1 : 0;
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
    bool too_long = (len > 64) ? 1 : 0;
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
