#ifndef CLIENT_EXCEPTION_HH
# define CLIENT_EXCEPTION_HH

#include <stdexcept>

namespace Application
{

  class ClientException : public std::runtime_error
  {
  public:
    ClientException(const std::string error) : std::runtime_error("Client exception : " + error) {}
  };

} /* namespace Application */

#endif /* CLIENT_EXCEPTION_HH */
