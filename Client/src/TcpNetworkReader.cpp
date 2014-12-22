#include	<iostream>
#include	<cstring>

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
}

void			TcpNetworkReader::onReadConnectionInternalError()
{
}

void			TcpNetworkReader::onReadConnectionOk()
{
}

void			TcpNetworkReader::onReadRoomCreateAlreadyExist()
{
}

void			TcpNetworkReader::onReadRoomCreateInternalError()
{
}

void			TcpNetworkReader::onReadRoomCreateOk()
{
}

void			TcpNetworkReader::onReadRoomJoinNotFound()
{
}

void			TcpNetworkReader::onReadRoomJoinIsFull()
{
}

void			TcpNetworkReader::onReadRoomJoinBadPswd()
{
}

void			TcpNetworkReader::onReadRoomJoinOk()
{
}

void			TcpNetworkReader::onReadMessage()
{
}

void			TcpNetworkReader::onReadGameStart()
{
}

void			TcpNetworkReader::onReadGameEnd()
{
}

void			TcpNetworkReader::onReadScore()
{
}

void			TcpNetworkReader::onReadPlayerInfo()
{
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
}

TcpNetworkReader::~TcpNetworkReader() {}
