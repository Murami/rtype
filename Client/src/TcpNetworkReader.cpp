#include	<iostream>
#include	<cstring>
#if defined(__linux__) || defined(__APPLE__)
# include <arpa/inet.h>
#endif

#include	"TcpConnection.hh"
#include	"TcpNetworkReader.hh"
#include	"ITcpNetworkListener.hh"
#include	"RtypeProtocol.hh"

TcpNetworkReader::TcpNetworkReader(TcpConnection& tcpConnection) :
  _tcpConnection(tcpConnection)
{
  _expectedPacket = RtypeProtocol::T_HEADER;
  _expectedSize = sizeof(RtypeProtocol::Header);
  _tcpListener = NULL;
  _initCallbacks();
}

int			TcpNetworkReader::run(Util::Mutex* mutex)
{
  char			buffer[4096];
  std::size_t		received;

  while (_tcpConnection.isReading() &&
	 _tcpConnection.socket().receive(&buffer[0], 4096, received) == sf::Socket::Done)
    {
      mutex->lock();
      for (size_t i = 0; i < received; i++)
	_buffer.push_back(buffer[i]);
      onReadData();
      mutex->unlock();
    }
  return (0);
}

void			TcpNetworkReader::onReadData()
{
  while (_buffer.size() >= _expectedSize)
    onReadHeader();
}

void			TcpNetworkReader::onReadHeader()
{
  RtypeProtocol::Header	header;

  for (size_t i = 0; i < sizeof(header); i++)
    {
      reinterpret_cast<char *>(&header)[i] = _buffer.front();
      _buffer.pop_front();
    }
  //header.type = ntohl(header.type);
  if (_callback.find(static_cast<RtypeProtocol::Type>(header.type)) != _callback.end())
    (this->*_callback[static_cast<RtypeProtocol::Type>(header.type)])();
}

void			TcpNetworkReader::onMagicBadVersion()
{
  _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
  _tcpListener->onMagicBadVersion();
}

void			TcpNetworkReader::onMagicAccept()
{
  _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
  _tcpListener->onMagicAccept();
}

void			TcpNetworkReader::onReadRoom()
{
  RtypeProtocol::Room	room;

  for (size_t i = 0; i < sizeof(room); i++)
    {
      reinterpret_cast<char *>(&room)[i] = _buffer.front();
      _buffer.pop_front();
    }
  _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
  _tcpListener->onRoomInfo(room);
}

void			TcpNetworkReader::onReadPing()
{
  RtypeProtocol::PingPong	ping;

  std::cout << "\044[46m" << __FUNCTION__ << "\033[0m\n";
  for (std::size_t i = 0; i < sizeof(ping); i++)
    {
      reinterpret_cast<char *>(&ping)[i] = _buffer.front();
      _buffer.pop_front();
    }
  _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
  _tcpListener->onPing(ping);
}

void			TcpNetworkReader::onReadConnectionAlreadyConnected()
{
  // Have to send to the view that this user is already connected
}

void			TcpNetworkReader::onReadConnectionInternalError(){}

void			TcpNetworkReader::onReadConnectionOk()
{
  // Have to send to the view that the screen can display the connected menu
}

void			TcpNetworkReader::onReadRoomCreateAlreadyExist()
{
  // Have to send to the view that this room already exists
}

void			TcpNetworkReader::onReadRoomCreateInternalError(){}

void			TcpNetworkReader::onReadRoomCreateOk()
{
  // Have to send to the view that the creation of the room is successful
}

void			TcpNetworkReader::onReadRoomJoinNotFound()
{
  // Have to send to the view that the room is not found
}

void			TcpNetworkReader::onReadRoomJoinIsFull()
{
  // Have to send to the view that there is no slot available in that room
}

void			TcpNetworkReader::onReadRoomJoinBadPswd()
{
  // Have to send to the view that the password is not correct
}

void			TcpNetworkReader::onReadRoomJoinOk()
{
  // Have to send to the view that joining the room is successful
  RtypeProtocol::Room	room;

  for (size_t i = 0; i < sizeof(room); i++)
    {
      reinterpret_cast<char *>(&room)[i] = _buffer.front();
      _buffer.pop_front();
    }
  _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
  _tcpListener->onRoomInfo(room);
  _tcpListener->onRoomJoinOk(room);
}

void			TcpNetworkReader::onReadMessage(){}

void			TcpNetworkReader::onReadGameStart()
{
  _tcpListener->onGameStart();
}

void			TcpNetworkReader::onReadGameEnd()
{
  // Have to send to the view that the game ended
}

void			TcpNetworkReader::onReadScore()
{
  // Have to notify the score to the view
}

void			TcpNetworkReader::onReadPlayerInfo()
{
  // Have to notify the player info to the view
}

void			TcpNetworkReader::onRoomHostLeft()
{
  _tcpListener->onHostLeftRoom();
}

void			TcpNetworkReader::onDeleteRoom()
{
  RtypeProtocol::Room	room;
  
  for (std::size_t i = 0; i < sizeof(room); i++)
    {
      reinterpret_cast<char *>(&room)[i] = _buffer.front();
      _buffer.pop_front();
    }
  _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
  _tcpListener->onDeleteRoom(room);
}

void			TcpNetworkReader::setExpectedPacket(RtypeProtocol::Type packetType)
{
  _expectedPacket = packetType;
}

void			TcpNetworkReader::setTcpNetworkListener(ITcpNetworkListener *listener)
{
  _tcpListener = listener;
}

RtypeProtocol::Type	TcpNetworkReader::getExpectedPacket()
{
  return (_expectedPacket);
}

void			TcpNetworkReader::_changeExpectedData(RtypeProtocol::Type type,
							   std::size_t size)
{
  _expectedPacket = type;
  _expectedSize = size;
}

void			TcpNetworkReader::_initCallbacks()
{
  _callback[RtypeProtocol::T_MAGIC_BAD_VERSION]			= &TcpNetworkReader::onMagicBadVersion;
  _callback[RtypeProtocol::T_MAGIC_ACCEPT]			= &TcpNetworkReader::onMagicAccept;
  _callback[RtypeProtocol::T_ROOMINFO]				= &TcpNetworkReader::onReadRoom;
  _callback[RtypeProtocol::T_PING]				= &TcpNetworkReader::onReadPing;
  _callback[RtypeProtocol::T_CONNECTION_ALREADY_CONNECTED]	= &TcpNetworkReader::onReadConnectionAlreadyConnected;
  _callback[RtypeProtocol::T_CONNECTION_INTERNAL_ERROR]		= &TcpNetworkReader::onReadConnectionInternalError;
  _callback[RtypeProtocol::T_CONNECTION_OK]			= &TcpNetworkReader::onReadConnectionOk;
  _callback[RtypeProtocol::T_ROOM_CREATE_ALREADY_EXIST]		= &TcpNetworkReader::onReadRoomCreateAlreadyExist;
  _callback[RtypeProtocol::T_ROOM_CREATE_INTERNAL_ERROR]	= &TcpNetworkReader::onReadRoomCreateInternalError;
  _callback[RtypeProtocol::T_ROOM_CREATE_OK]			= &TcpNetworkReader::onReadRoomCreateOk;
  _callback[RtypeProtocol::T_ROOM_JOIN_NOT_FOUND]		= &TcpNetworkReader::onReadRoomJoinNotFound;
  _callback[RtypeProtocol::T_ROOM_JOIN_IS_FULL]			= &TcpNetworkReader::onReadRoomJoinIsFull;
  _callback[RtypeProtocol::T_ROOM_JOIN_BAD_PSWD]		= &TcpNetworkReader::onReadRoomJoinBadPswd;
  _callback[RtypeProtocol::T_ROOM_JOIN_OK]			= &TcpNetworkReader::onReadRoomJoinOk;
  _callback[RtypeProtocol::T_MSG]				= &TcpNetworkReader::onReadMessage;
  _callback[RtypeProtocol::T_GAMESTART]				= &TcpNetworkReader::onReadGameStart;
  _callback[RtypeProtocol::T_GAMEEND]				= &TcpNetworkReader::onReadGameEnd;
  _callback[RtypeProtocol::T_SCORE]				= &TcpNetworkReader::onReadScore;
  _callback[RtypeProtocol::T_PLAYERINFO]			= &TcpNetworkReader::onReadPlayerInfo;
  _callback[RtypeProtocol::T_ROOM_HOST_LEAVED]			= &TcpNetworkReader::onRoomHostLeft;
  _callback[RtypeProtocol::T_ROOM_DELETE]			= &TcpNetworkReader::onDeleteRoom;
}

TcpNetworkReader::~TcpNetworkReader() {}
