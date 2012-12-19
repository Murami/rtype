#ifndef NETWORK_EXCEPTION_HH
# define NETWORK_EXCEPTION_HH

#include <stdexcept>
#include <iostream>

namespace Network
{

  class NetworkException : public std::runtime_error
  {
  public:
    NetworkException(const std::string error) : std::runtime_error("Network exception : " + error) {}
  };

} /* namespace Network */

#endif /* NETWORK_EXCEPTION_HH */
