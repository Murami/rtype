#include <iostream>
#include <cstring>

#include "UdpConnection.hh"
#include "RtypeProtocol.hh"
#include "UdpNetworkReader.hh"

UdpNetworkReader::UdpNetworkReader(UdpConnection& connection) :
  _udpConnection(connection)
{
  _listener = NULL;
}

int			UdpNetworkReader::run(Util::Mutex* mutex)
{
  char			buffer[4096];
  std::size_t		received;
  sf::IpAddress		ip(_udpConnection.getIpFromConf());
  unsigned short	port;

  port = static_cast<unsigned short>(_udpConnection.getPortFromConf());
  while (_udpConnection.isReading() && _udpConnection.socket().receive(reinterpret_cast<void *>(&buffer[0]), 4096, received, ip, port) == sf::Socket::Done)
    {
      mutex->lock();
      onReadData(buffer);
      mutex->unlock();
    }
  return (0);
}

void	UdpNetworkReader::onReadData(char *buffer)
{
  RtypeProtocol::Header header;

  std::cout << "\033[41mreading data UDP\033[0m" << std::endl;
  std::memcpy(&header, buffer, sizeof(header));
  switch (header.type)
    {
    case RtypeProtocol::T_MAPCHANGE:
      std::cout << "[UDP]: Received map change info" << std::endl;
      break;
    case RtypeProtocol::T_PLAYERINFO:
      std::cout << "[UDP]: Received player info" << std::endl;
      break;
    case RtypeProtocol::T_POSITION:
      std::cout << "[UDP]: Received position info" << std::endl;
      break;
    case RtypeProtocol::T_SPAWN:
      std::cout << "[UDP]: Received spawn info" << std::endl;
      break;
    case RtypeProtocol::T_EVENT:
      std::cout << "[UDP]: Received event info" << std::endl;
      break;
    case RtypeProtocol::T_DESTRUCTION:
      std::cout << "[UDP]: Received destruction info" << std::endl;
      break;
    case RtypeProtocol::T_LIFE:
      std::cout << "[UDP]: Received life info" << std::endl;
      break;
    case RtypeProtocol::T_BONUS:
      std::cout << "[UDP]: Received bonus info" << std::endl;
      break;
    case RtypeProtocol::T_HIT:
      std::cout << "[UDP]: Received hit info" << std::endl;
      break;
    case RtypeProtocol::T_DEATH:
      std::cout << "[UDP]: Received death info" << std::endl;
      break;
    case RtypeProtocol::T_ENTITYINFOS:
      std::cout << "[UDP]: Received entity info" << std::endl;
      break;
    default:
      std::cout << "[UDP]: Received unknown header" << std::endl;
      break;
    }
}

void		UdpNetworkReader::setUdpNetworkListener(IUdpNetworkListener *listener)
{
  _listener = listener;
}

UdpNetworkReader::~UdpNetworkReader()
{
}
