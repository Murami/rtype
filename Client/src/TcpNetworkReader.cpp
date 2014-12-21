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

  std::cout << "\033[42mBeginning to read...\033[0m" << std::endl;
  while (_tcpConnection.isReading() &&
	 _tcpConnection.socket().receive(&buffer[0], 4096, received) == sf::Socket::Done)
    {
      std::cout << "\033[43mTreating datas...\033[0m" << std::endl;
      mutex->lock();
      for (size_t i = 0; i < received; i++)
	_buffer.push_back(buffer[i]);
      onReadData();
      mutex->unlock();
    }
  std::cout << "\033[44mEnding Thread...\033[0m" << std::endl;
  return (0);
}

void			TcpNetworkReader::onReadData()
{
  std::cout << "\033[41m" << __FUNCTION__ << "\033[0m" << std::endl;

  while (_buffer.size() >= _expectedSize)
    {
      switch (_expectedPacket)
	{
	case RtypeProtocol::T_HEADER:
	  onReadHeader();
	  break;
	case RtypeProtocol::T_ROOMINFO:
	  onReadRoom();
	  break;
	case RtypeProtocol::T_PING:
	  onReadPing();
	  break;
	default:
	  break;
	}
    }
}

void			TcpNetworkReader::onReadPing()
{
  // RtypeProtocol::Header		header;
  // RtypeProtocol::PingPong	pingPong;

  // header.type = RtypeProtocol::T_PONG;
  // header.data_size = sizeof(RtypeProtocol::PingPong);
}

void			TcpNetworkReader::onReadRoom()
{
  RtypeProtocol::Room	room;

  for (size_t i = 0; i < sizeof(room); i++)
    {
      reinterpret_cast<char *>(&room)[i] = _buffer.front();
      _buffer.pop_front();
    }
  _expectedPacket = RtypeProtocol::T_HEADER;
  _expectedSize = sizeof(RtypeProtocol::Room);
  _tcpListener->onRoomInfo(room);
}

void			TcpNetworkReader::onReadHeader()
{
  RtypeProtocol::Header	header;

  for (size_t i = 0; i < sizeof(header); i++)
    {
      reinterpret_cast<char *>(&header)[i] = _buffer.front();
      _buffer.pop_front();
    }
  switch (header.type)
    {
    case RtypeProtocol::T_MAGIC_BAD_VERSION:
      std::cout << "Received bad magic version" << std::endl;
      _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
      _tcpListener->onMagicBadVersion();
      break;

    case RtypeProtocol::T_MAGIC_ACCEPT:
      std::cout << "Received good magic number" << std::endl;
      _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
      _tcpListener->onMagicAccept();
      break;

    case RtypeProtocol::T_CONNECTION_ALREADY_CONNECTED:
      std::cout << "This user is already connected" << std::endl;
      break;

    case RtypeProtocol::T_CONNECTION_INTERNAL_ERROR:
      std::cout << "CONNECTION: internal error" << std::endl;
      break;

    case RtypeProtocol::T_CONNECTION_OK:
      std::cout << "Connection success" << std::endl;
      _changeExpectedData(RtypeProtocol::T_HEADER, sizeof(RtypeProtocol::Header));
      break;
    case RtypeProtocol::T_ROOMINFO:
      std::cout << "Received room info" << std::endl;
      _changeExpectedData(RtypeProtocol::T_ROOMINFO, sizeof(RtypeProtocol::Room));
      break;

    case RtypeProtocol::T_ROOM_CREATE_ALREADY_EXIST:
      std::cout << "Room creation failed : already exist" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_CREATE_INTERNAL_ERROR:
      std::cout << "Room creating failed : internal error" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_CREATE_OK:
      std::cout << "Room creation success" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_JOIN_NOT_FOUND:
      std::cout << "Joining room failed : Room not found" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_JOIN_IS_FULL:
      std::cout << "Joining room failed : Room is full" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_JOIN_BAD_PSWD:
      std::cout << "Joining room failed : Bad password" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_JOIN_OK:
      std::cout << "Joining room success" << std::endl;
      break;

    case RtypeProtocol::T_ROOM_EXIT_OK:
      std::cout << "Exiting room" << std::endl;
      break;

    case RtypeProtocol::T_PING:
      std::cout << "Pinging server" << std::endl;
      _changeExpectedData(RtypeProtocol::T_PING, sizeof(RtypeProtocol::PingPong));
      break;

    case RtypeProtocol::T_MSG:
      std::cout << "Message received" << std::endl;
      break;

    case RtypeProtocol::T_GAMESTART:
      std::cout << "Game starting" << std::endl;
      break;

    case RtypeProtocol::T_GAMEEND:
      std::cout << "Game ending" << std::endl;
      break;

    case RtypeProtocol::T_SCORE:
      std::cout << "Score" << std::endl;
      break;

    case RtypeProtocol::T_PLAYERINFO:
      std::cout << "Player informations" << std::endl;
      break;

    default:
      std::cout << "unknown header" << std::endl;
      break;
    }
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
  // _callback[RtypeProtocol::T_MAGIC_BAD_VERSION] = &ITcpNetworkListener::onMagicBadVersion;
}

TcpNetworkReader::~TcpNetworkReader() {}
