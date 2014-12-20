#include "Util.hh"

namespace Util
{
  void		stringncopy(std::string& string, const char* cstring, unsigned int size)
  {
    string = std::string(cstring, strnlen(cstring, size));
  }

  void		stringncopy(std::string& string, const uint8_t* cstring, unsigned int size)
  {
    const char	*str = reinterpret_cast<const char*>(cstring);

    string = std::string(str, strnlen(str, size));
  }
};
