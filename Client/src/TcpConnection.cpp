#include	<SFML/System/Time.hpp>

#include	"Thread.hpp"
#include	"ConnectionConfiguration.hh"
#include	"TcpConnection.hh"

TcpConnection::TcpConnection(const ConnectionConfiguration& conf) :
  _conf(conf)
{
  _reader = new NetworkReader(*this);
  _socket.setBlocking(false);
}

void		TcpConnection::startRead()
{
  _reader->start();
  _running = true;
}

void		TcpConnection::stopRead()
{
  _reader->cancel();
  _running = false;
}

void		TcpConnection::joinRead()
{
  _reader->join();
}

bool		TcpConnection::isRunning() const
{
  return (_running);
}

sf::TcpSocket&	TcpConnection::socket()
{
  return (_socket);
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
