#ifndef PROTOCOL_EXCEPTION_HH
# define PROTOCOL_EXCEPTION_HH

#include <stdexcept>
#include <iostream>

namespace RtypeProtocol
{
  class ProtocolException : public std::runtime_error
  {
  public:
    ProtocolException(const std::string error) : std::runtime_error("Protocol exception : " + error) {}
  };

} /* namespace RtypeProtocol */

#endif /* PROTOCOL_EXCEPTION_HH */
