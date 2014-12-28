#include <iostream>

#include "UdpNetworkReader.hh"
#include "UdpNetworkWriter.hh"
#include "ConnectionConfiguration.hh"
#include "UdpConnection.hh"

UdpConnection::UdpConnection(const ConnectionConfiguration& conf, Util::Mutex *mutex):
  _conf(conf)
{
  _listener = NULL;
  _reader = new UdpNetworkReader(*this);
  _reader->setParam(mutex);
}

void			UdpConnection::startRead()
{
  _reading = true;
  _reader->start();
}

void			UdpConnection::stopRead()
{
  _reading = false;
  _reader->cancel();
}

void			UdpConnection::joinRead()
{
  _reader->join();
}

bool			UdpConnection::isReading() const
{
  return (_reading);
}

uint16_t		UdpConnection::getLocalPort()
{
  return (_socket.getLocalPort());
}

bool			UdpConnection::connect()
{
  sf::Socket::Status ret;

  if ((ret = _socket.bind(sf::Socket::AnyPort)) != sf::Socket::Done)
    {
      switch (ret)
  	{
  	case sf::Socket::NotReady:
  	  std::cerr << "UDP Socket is not ready" << std::endl;
  	  break;
  	case sf::Socket::Disconnected:
  	  std::cerr << "UDP Socket is disconnected" << std::endl;
  	  break;
  	case sf::Socket::Error:
  	  std::cerr << "UDP Socket is on unknown error" << std::endl;
  	  break;
  	default:
  	  break;
  	}
      return (false);
    }
  return (true);
}

bool			UdpConnection::write(void *data, std::size_t count)
{
  sf::Socket::Status ret;

  // std::cout << _conf.getPortUdp() << std::endl;
  if ((ret = _socket.send(data, count, _conf.getIp(), _conf.getPortUdp())) != sf::Socket::Done)
    {
      switch (ret)
	{
	case sf::Socket::NotReady:
	  std::cerr << "UDP Socket is not ready" << std::endl;
	  break;
	case sf::Socket::Disconnected:
	  std::cerr << "UDP Socket is disconnected" << std::endl;
	  break;
	case sf::Socket::Error:
	  std::cerr << "UDP Socket is on unknown error" << std::endl;
	  break;
	default:
	  break;
	}
      return (false);
    }
  return (true);
}

void			UdpConnection::setUdpNetworkListener(IUdpNetworkListener *listener)
{
  _listener = listener;
  _reader->setUdpNetworkListener(listener);
}

sf::UdpSocket&		UdpConnection::socket()
{
  return (_socket);
}

const std::string&	UdpConnection::getIpFromConf() const
{
  return (_conf.getIp());
}

int			UdpConnection::getPortFromConf() const
{
  return (_conf.getPortUdp());
}

UdpConnection::~UdpConnection()
{
}
