#include	<SFML/System/Time.hpp>

#include	"Thread.hpp"
#include	"ConnectionConfiguration.hh"
#include	"TcpConnection.hh"

TcpConnection::TcpConnection(const ConnectionConfiguration& conf, Util::Mutex *mutex) :
  _conf(conf)
{
  _reader = new TcpNetworkReader(*this);
  _reader->setParam(mutex);
  _writer = new TcpNetworkWriter(*this);
}

void		TcpConnection::setTcpNetworkListener(ITcpNetworkListener *listener)
{
  _reader->setTcpNetworkListener(listener);
}

void		TcpConnection::startRead()
{
  _reading = true;
  _reader->start();
}

void		TcpConnection::stopRead()
{
  _reading = false;
  _reader->cancel();
}

void		TcpConnection::joinRead()
{
  _reader->join();
}

bool		TcpConnection::isReading() const
{
  return (_reading);
}

void		TcpConnection::startWrite()
{
  _writing = true;
  _writer->start();
}

void		TcpConnection::stopWrite()
{
  _writing = false;
  _writer->cancel();
}

void		TcpConnection::joinWrite()
{
  _writer->join();
}

bool		TcpConnection::isWriting() const
{
  return (_writing);
}

sf::TcpSocket&	TcpConnection::socket()
{
  return (_socket);
}

bool		TcpConnection::connect()
{
  sf::Socket::Status ret;

  if ((ret = _socket.connect(_conf.getIp(), _conf.getPortTcp())) != sf::Socket::Done)
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
	}
      return (false);
    }
  return (true);
}

bool		TcpConnection::write(void *data, std::size_t count)
{
  _writer->sendData(data, count);
  return (true);
}

std::ostream&	operator<<(std::ostream& os, const ConnectionConfiguration& conf)
{
  os << "[IP]:\t" << conf.getIp() << std::endl << "[PORT]:\t" << conf.getPortTcp();
  return (os);
}

TcpConnection::~TcpConnection() {}
