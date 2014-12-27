#include "EndPoint.hh"

namespace Network
{
  EndPoint::EndPoint(unsigned int port, const std::string & host) : _port(port), _host(host) {}

  EndPoint::EndPoint(const EndPoint& endpoint)
  {
    *this = endpoint;
  }

  EndPoint::~EndPoint() {}

  EndPoint&		EndPoint::operator=(const EndPoint& endpoint)
  {
    _port = endpoint._port;
    _host = endpoint._host;

    return (*this);
  }

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

  bool			EndPoint::operator==(const EndPoint& endpoint) const
  {
    return (endpoint._port == _port && endpoint._host == _host);
  }

  bool			EndPoint::operator!=(const EndPoint& endpoint) const
  {
    return (!(*this == endpoint));
  }

  bool			EndPoint::operator<=(const EndPoint& endpoint) const
  {
    return (_host < endpoint._host || (_host == endpoint._host && _port <= endpoint._port));
  }

  bool			EndPoint::operator>=(const EndPoint& endpoint) const
  {
    return (_host > endpoint._host || (_host == endpoint._host && _port >= endpoint._port));
  }

  bool			EndPoint::operator<(const EndPoint& endpoint) const
  {
    return (_host < endpoint._host || (_host == endpoint._host && _port < endpoint._port));
  }

  bool			EndPoint::operator>(const EndPoint& endpoint) const
  {
    return (_host > endpoint._host || (_host == endpoint._host && _port > endpoint._port));
  }
}
