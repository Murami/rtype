#ifndef UTIL_UTIL
#define UTIL_UTIL

#include <string>
#include <cstring>
#include <cstdint>

namespace Util
{
  void		stringncopy(std::string& string, const char* cstring, unsigned int size);
  void		stringncopy(std::string& string, const uint8_t* cstring, unsigned int size);
};

#endif /* UTIL_UTIL */
