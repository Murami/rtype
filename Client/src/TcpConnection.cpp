#include	<SFML/System/Time.hpp>
#include	"ConnectionConfiguration.hh"
#include	"TcpConnection.hh"

TcpConnection::TcpConnection(const ConnectionConfiguration& conf) : _conf(conf)
{
}

bool		TcpConnection::connect()
{
  if (_socket.connect(_conf.getIp(), _conf.getPort()) != sf::Socket::Done)
    {
      std::cerr << "Unable to connect to remote host : "
		<< std::endl << _conf << std::endl;
      return (false);
    }
  return (true);
}

std::ostream&	operator<<(std::ostream& os, const ConnectionConfiguration& conf)
{
  os << "[IP]:\t" << conf.getIp() << std::endl << "[PORT]:\t" << conf.getPort();
  os << std::endl;
  return (os);
}

TcpConnection::~TcpConnection() {}
