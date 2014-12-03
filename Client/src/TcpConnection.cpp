#include	<SFML/System/Time.hpp>
#include	"ConnectionConfiguration.hh"
#include	"TcpConnection.hh"

TcpConnection::TcpConnection(const ConnectionConfiguration& conf) : _conf(conf)
{
}

bool		TcpConnection::connect()
{
  sf::Time	time;

  time.seconds(10);
  if (!_socket.connect(_conf.getIp(), _conf.getPort()))
    {
      std::cerr << "Unable to connect to remote host : " << _conf << std::endl;
      return (false);
    }
  return (true);
}

TcpConnection::~TcpConnection() {}

std::ostream&	operator<<(std::ostream& os, const ConnectionConfiguration& conf)
{
  os << "[IP]:\t" << conf.getIp() << std::endl << "[PORT]:\t" << conf.getPort();
  os << std::endl;
  return (os);
}
