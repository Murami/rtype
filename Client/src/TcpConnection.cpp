#include	<SFML/System/Time.hpp>
# include	<boost/bind.hpp>

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

bool		TcpConnection::write(const void *data, std::size_t count)
{
  sf::Socket::Status	ret;

  if ((ret = _socket.send(data, count)) != sf::Socket::Done)
    {
      switch (ret)
  	{
  	case sf::Socket::NotReady:
  	  std::cerr << "Socket write error: socket is not ready" << std::endl;
  	  break;
  	case sf::Socket::Disconnected:
  	  std::cerr << "Socket write error: socket is disconnected" << std::endl;
  	  break;
  	case sf::Socket::Error:
  	  std::cerr << "Socket write error: socket is on error" << std::endl;
  	  break;
  	default:
  	  break;
  	  return (false);
  	}
    }
  return (true);
}

std::ostream&	operator<<(std::ostream& os, const ConnectionConfiguration& conf)
{
  os << "[IP]:\t" << conf.getIp() << std::endl << "[PORT]:\t" << conf.getPort();
  return (os);
}

TcpConnection::~TcpConnection() {}
