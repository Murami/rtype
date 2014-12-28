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
  _callbacks[RtypeProtocol::T_MAPCHANGE]	= &UdpNetworkReader::onReadMapChange;
  _callbacks[RtypeProtocol::T_PLAYERINFO]	= &UdpNetworkReader::onReadPlayerInfo;
  _callbacks[RtypeProtocol::T_POSITION]		= &UdpNetworkReader::onReadPosition;
  _callbacks[RtypeProtocol::T_SPAWN]		= &UdpNetworkReader::onReadSpawn;
  _callbacks[RtypeProtocol::T_EVENT]		= &UdpNetworkReader::onReadEvent;
  _callbacks[RtypeProtocol::T_DESTRUCTION]	= &UdpNetworkReader::onReadDestruction;
  _callbacks[RtypeProtocol::T_LIFE]		= &UdpNetworkReader::onReadLife;
  _callbacks[RtypeProtocol::T_BONUS]		= &UdpNetworkReader::onReadBonus;
  _callbacks[RtypeProtocol::T_HIT]		= &UdpNetworkReader::onReadHit;
  _callbacks[RtypeProtocol::T_DEATH]		= &UdpNetworkReader::onReadDeath;
  _callbacks[RtypeProtocol::T_ENTITYINFOS]	= &UdpNetworkReader::onReadEntityInfos;
}

int			UdpNetworkReader::run(Util::Mutex* mutex)
{
  char			buffer[4096];
  std::size_t		received;
  sf::IpAddress		ip(_udpConnection.getIpFromConf());
  unsigned short	port;

  port = static_cast<unsigned short>(_udpConnection.getPortFromConf());
  std::cout << "\033[37mEntering UDP Reading thread\033[0m" << std::endl;
<<<<<<< HEAD
  while (_udpConnection.isReading() && _udpConnection.socket().receive(reinterpret_cast<char *>(&buffer[0]), 4096, received, ip, port) == sf::Socket::Done)
  {
    std::cout << "\033[36mInto the while\033[0m" << std::endl;
    mutex->lock();
    onReadData(buffer);
    mutex->unlock();
  }
=======
  while (_udpConnection.isReading() && _udpConnection.socket().receive(buffer, 4096, received, ip, port) == sf::Socket::Done)
    {
      mutex->lock();
      std::cout << "\033[36mInto the while\033[0m" << std::endl;
      onReadData(buffer);
      mutex->unlock();
    }
>>>>>>> c3a31d86f3d817360b208339d1e7aa0321b6a7f9
  std::cout << "\033[35mGetting of the UDP reading thread\033[0m" << std::endl;
  return (0);
}

void	UdpNetworkReader::onReadMapChange(char *)
{
}

void	UdpNetworkReader::onReadPlayerInfo(char *)
{
}

void	UdpNetworkReader::onReadPosition(char *buffer)
{
  RtypeProtocol::PositionEvent	position;

  std::memcpy(&position, &buffer[sizeof(RtypeProtocol::Header)], sizeof(position));
  position.id = ntohl(position.id);
  position.position.x = ntohl(position.position.x);
  position.position.y = ntohl(position.position.y);
  position.position.state = ntohl(position.position.state);
  std::cout << "\033[45mRECEIVED POSITION\033[0m" << std::endl;
  _listener->onPosition(position);
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
  std::cout << "\033[44mRECEIVED SPAWN and sending to listener\033[0m" << std::endl;
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
  (this->*_callbacks[(RtypeProtocol::Type)header.type])(buffer);
}

void		UdpNetworkReader::setUdpNetworkListener(IUdpNetworkListener *listener)
{
  _listener = listener;
}

UdpNetworkReader::~UdpNetworkReader()
{
}
