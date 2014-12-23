#include "EndPoint.hh"

namespace Network
{

  EndPoint::EndPoint(unsigned int port, const std::string & host) : _port(port), _host(host) {}

  EndPoint::~EndPoint() {}

  void			EndPoint::setPort(unsigned int port)
  {
    _port = port;
  }

  void			EndPoint::setHost(const std::string & host)
  {
    _host = host;
  }

  unsigned int		EndPoint::getPort() const
  {
    return (_port);
  }

  const std::string &	EndPoint::getHost() const
  {
    return (_host);
  }

}
