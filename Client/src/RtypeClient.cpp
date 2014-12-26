#include	<cstring>
#include	<stdexcept>

#if defined(__linux__) || defined(__APPLE__)
# include <arpa/inet.h>
#elif defined(WIN32)
# include <Winsock2.h>
# include <windows.h>
#endif

#include	"MenuController.hh"
#include	"MenuView.hh"
#include	"TcpConnection.hh"
#include	"UdpConnection.hh"
#include	"RtypeClient.hh"
#include	"SoundManager.hh"
#include	"GameController.hh"
#include	"GameView.hh"
#include	"RtypeProtocol.hh"

#ifdef __linux__
# include <X11/Xlib.h>
#endif

RtypeClient::RtypeClient()
{
#ifdef __linux__
  XInitThreads();
#endif
  _mutex.lock();
  _tcpConnection = new TcpConnection(_configuration, &_mutex);
  _tcpConnection->setTcpNetworkListener(this);
  _udpConnection = new UdpConnection(_configuration, &_mutex);
  _udpConnection->setUdpNetworkListener(this);
}

RtypeClient::~RtypeClient()
{
  delete _menuView;
  delete _menuController;
  delete _window;
}

void		RtypeClient::run()
{
  RtypeProtocol::Header header;
  RtypeProtocol::Magic	magic;

  _window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
					       sf::VideoMode::getDesktopMode().height),
				 "Rtype");

  _window->setKeyRepeatEnabled(false);

  _menuView = new MenuView(*_window);
  _menuController = new MenuController(*_menuView);
  _gameView = new GameView();
  _gameController = new GameController(*_gameView);

  _gameView->addObserver(_gameController);
  _gameController->setGameListener(this);

  _menuView->addObserver(_menuController);
  _menuController->setMenuListener(this);

  if (!_tcpConnection->connect())
    throw (std::runtime_error("TCP connect"));

  if (!_udpConnection->connect())
    throw (std::runtime_error("UDP connect"));

  header.type = RtypeProtocol::T_MAGIC;
  header.data_size = sizeof(magic);

  magic.minor_version = htonl(RtypeProtocol::minor_version);
  magic.major_version = htonl(RtypeProtocol::major_version);

  std::memset(&magic.proto_name[0], 0, PROTO_NAME_SIZE);
  std::memcpy(reinterpret_cast<char *>(&magic.proto_name[0]),
  	      RtypeProtocol::proto_name,
  	      std::strlen(reinterpret_cast<const char *>(RtypeProtocol::proto_name)));
  char *buffer = new char[sizeof(header) + sizeof(magic)];
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &magic, sizeof(magic));

  _tcpConnection->startRead();
  _tcpConnection->startWrite();

  _udpConnection->startRead();

  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(magic));

  SoundManager::Play("theme", true);
  _menuView->run(*_window, &_mutex);
  _tcpConnection->stopRead();
  _tcpConnection->stopWrite();
  _tcpConnection->joinRead();
  _tcpConnection->joinWrite();

  _udpConnection->stopRead();
  _udpConnection->joinRead();
}

// IUdpNetworkListener

void	RtypeClient::onPlayerInfo()
{
}

void	RtypeClient::onPosition()
{
}

void	RtypeClient::onSpawn()
{
}

void	RtypeClient::onDestruction()
{
}

void	RtypeClient::onLife()
{
}

void	RtypeClient::onBonus()
{
}

void	RtypeClient::onHit()
{
}

void	RtypeClient::onDeath()
{
}

void	RtypeClient::onEntityInfo()
{
}

// IKeyListener

void	RtypeClient::onKeyEvent(std::size_t event)
{
  RtypeProtocol::Header header;
  char		buffer[sizeof(size_t) + sizeof(header)];

  std::cout << static_cast<int>(event) << std::endl;
  header.type = RtypeProtocol::T_EVENT;
  header.data_size = sizeof(event);
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &event, sizeof(event));
  _udpConnection->write(&buffer[0], sizeof(event) + sizeof(header));
}

// ITcpNetworkListener

void	RtypeClient::onMagicBadVersion()
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  throw (std::runtime_error("connect to server : bad magic version"));
}

void	RtypeClient::onMagicAccept()
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnectionAlreadyConnected()
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnectionInternalError()
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnectionOk()
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onDisconnection()
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomInfo(RtypeProtocol::Room room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  if (room.alive)
    _menuController->addToRoomList(room);
  else
    _menuController->deleteFromRoomList(room);
}

void	RtypeClient::onRoomCreateAlreadyExist(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomCreateInternalError(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomCreateOk(RtypeProtocol::Room room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  onRoomJoinOk(room);
}

void	RtypeClient::onRoomJoinNotFound(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinIsFull(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinBadPswd(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinOk(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomExitOk(RtypeProtocol::Room)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onPing(RtypeProtocol::PingPong)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onGameStart()
{
  _menuView->stop();
  _gameView->run(*_window, &_mutex);
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onGameEnd(RtypeProtocol::EndGame)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onScore(RtypeProtocol::Score)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

void	RtypeClient::onMessage(RtypeProtocol::Message)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
}

bool	RtypeClient::onConnectFromMenu(const std::string & login)
{
  RtypeProtocol::Header header;
  RtypeProtocol::User user;
  char	*buffer = new char[sizeof(header) + sizeof(user)];

  SoundManager::Play("bip");
  header.type = RtypeProtocol::T_CONNECTION;
  header.data_size = sizeof(RtypeProtocol::User);
  strcpy(reinterpret_cast<char *>(&user.username[0]), login.c_str());
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &user, sizeof(user));
  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(user));
  return (true);
}

bool	RtypeClient::onDisconnectFromMenu()
{
  RtypeProtocol::Header header;

  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  header.type = RtypeProtocol::T_DISCONNECTION;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
  return (true);
}

bool	RtypeClient::onRoomConnectFromMenu(int id, const std::string& pass)
{
  RtypeProtocol::Header header;
  RtypeProtocol::RoomConnection room;
  char buffer[sizeof(header) + sizeof(room)];

  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  header.type = RtypeProtocol::T_ROOM_JOIN;
  header.data_size = sizeof(room);
  room.id = id;
  strcpy(reinterpret_cast<char *>(room.pass_md5), pass.c_str());
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &room, sizeof(room));
  _tcpConnection->write(&buffer, sizeof(header) + sizeof(room));
  return (true);
}

bool	RtypeClient::onRoomLeaveFromMenu()
{
  RtypeProtocol::Header header;

  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  header.type = RtypeProtocol::T_ROOM_EXIT;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
  return (true);
}

bool	RtypeClient::onUserReadyFromMenu()
{
  RtypeProtocol::Header header;

  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  header.type = RtypeProtocol::T_READY;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
  return (true);
}

bool	RtypeClient::onUserMessageFromMenu(RtypeProtocol::Message)
{
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onCreateRoomFromMenu(const std::string& roomName,
					  const std::string& password)
{
  RtypeProtocol::Header header;
  RtypeProtocol::Room	room;
  char			buffer[sizeof(header) + sizeof(room)];

  std::cout << __FILE__ << ":" << __LINE__ << "\t" << __FUNCTION__ << std::endl;
  header.type = RtypeProtocol::T_ROOM_CREATE;
  header.data_size = sizeof(room);
  std::memset(&room, 0, sizeof(room));
  strcpy(reinterpret_cast<char *>(room.room_name), roomName.c_str());
  strcpy(reinterpret_cast<char *>(room.pass_md5), password.c_str());
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &room, sizeof(room));
  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(room));
  return (true);
}
