#include <iostream>
#include <cstring>
#if defined(__linux__) || defined(__APPLE__)
# include <arpa/inet.h>
#endif

#include "UdpConnection.hh"
#include "RtypeProtocol.hh"
#include "UdpNetworkReader.hh"
#include "IUdpNetworkListener.hh"

UdpNetworkReader::UdpNetworkReader(UdpConnection& connection) :
  _udpConnection(connection)
{
  _listener = NULL;
  _callbacks[RtypeProtocol::T_MAPCHANGE] = &UdpNetworkReader::onReadMapChange;
  _callbacks[RtypeProtocol::T_PLAYERINFO] = &UdpNetworkReader::onReadPlayerInfo;
  _callbacks[RtypeProtocol::T_POSITION] = &UdpNetworkReader::onReadPosition;
  _callbacks[RtypeProtocol::T_SPAWN] = &UdpNetworkReader::onReadSpawn;
  _callbacks[RtypeProtocol::T_EVENT] = &UdpNetworkReader::onReadEvent;
  _callbacks[RtypeProtocol::T_DESTRUCTION] = &UdpNetworkReader::onReadDestruction;
  _callbacks[RtypeProtocol::T_LIFE] = &UdpNetworkReader::onReadLife;
  _callbacks[RtypeProtocol::T_BONUS] = &UdpNetworkReader::onReadBonus;
  _callbacks[RtypeProtocol::T_HIT] = &UdpNetworkReader::onReadHit;
  _callbacks[RtypeProtocol::T_DEATH] = &UdpNetworkReader::onReadDeath;
  _callbacks[RtypeProtocol::T_ENTITYINFOS] = &UdpNetworkReader::onReadEntityInfos;
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

void	UdpNetworkReader::onReadMapChange(char *)
{
}

void	UdpNetworkReader::onReadPlayerInfo(char *)
{
}

void	UdpNetworkReader::onReadPosition(char *)
{
}

void	UdpNetworkReader::onReadSpawn(char *buffer)
{
  RtypeProtocol::Spawn spawn;
  std::memcpy(&spawn, &buffer[sizeof(RtypeProtocol::Header)], sizeof(spawn));
  spawn.id = ntohl(spawn.id);
  spawn.type = ntohl(spawn.type);
  spawn.position.x = ntohl(spawn.position.x);
  spawn.position.y = ntohl(spawn.position.y);
  spawn.position.orientation = ntohl(spawn.position.orientation);
  spawn.position.state = ntohl(spawn.position.state);
  spawn.life = ntohl(spawn.life);
  _listener->onSpawn(spawn);
}

void	UdpNetworkReader::onReadEvent(char *)
{
}

void	UdpNetworkReader::onReadDestruction(char *)
{
}

void	UdpNetworkReader::onReadLife(char *)
{
}

void	UdpNetworkReader::onReadBonus(char *)
{
}

void	UdpNetworkReader::onReadHit(char *)
{
}

void	UdpNetworkReader::onReadDeath(char *)
{
}

void	UdpNetworkReader::onReadEntityInfos(char *)
{
}

void	UdpNetworkReader::onReadData(char *buffer)
{
  RtypeProtocol::Header header;

  std::cout << "\033[41mreading data UDP\033[0m" << std::endl;
  std::memcpy(&header, buffer, sizeof(header));
  header.type = ntohl(header.type);
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
      onReadSpawn(buffer);
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
