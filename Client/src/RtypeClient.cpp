#include	<cstring>
#include	<stdexcept>

#include	<arpa/inet.h>

#include	"MenuController.hh"
#include	"MenuView.hh"
#include	"TcpConnection.hh"
#include	"RtypeClient.hh"
#include	"SoundManager.hh"
#include	"GameController.hh"
#include	"GameView.hh"
#include	"RtypeProtocol.hh"

RtypeClient::RtypeClient()
{
  _mutex.lock();
  _tcpConnection = new TcpConnection(_configuration, &_mutex);
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

  _menuView->addObserver(_menuController);
  _menuController->setMenuListener(this);

  if (!_tcpConnection->connect())
    throw (std::runtime_error("Connect"));

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
  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(magic));

  SoundManager::Play("theme", true);
  _menuView->run(*_window, &_mutex);
  _tcpConnection->stopRead();
  _tcpConnection->joinRead();
}

void	RtypeClient::onKeyEvent(RtypeEvent::eKeyEvent event)
{
  RtypeProtocol::Header header;

  header.type = RtypeProtocol::T_EVENT;
  header.data_size = sizeof(event);
  // Faire concatenation buffer
  _tcpConnection->write(&header, sizeof(header));
  _tcpConnection->write(&event, sizeof(event));
}

void	RtypeClient::onMagicBadVersion(RtypeProtocol::Magic)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onMagicAccept(RtypeProtocol::Magic)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnectionAlreadyConnected()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnectionInternalError()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnectionOk()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onDisconnection()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomInfo(RtypeProtocol::Room room)
{
  std::cout << __FUNCTION__ << std::endl;
  // if (room.alive)
  //   _menuController->addToRoomList(room);
  // else
  //   _menuController->deleteFromRoomList(room);
}

void	RtypeClient::onRoomCreateAlreadyExist(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomCreateInternalError(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomCreateOk(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinNotFound(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinIsFull(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinBadPswd(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomJoinOk(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomExitOk(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onPing(RtypeProtocol::PingPong)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onGameStart()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onGameEnd(RtypeProtocol::EndGame)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onScore(RtypeProtocol::Score)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onMessage(RtypeProtocol::Message)
{
  std::cout << __FUNCTION__ << std::endl;
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
  // Send disconnection datas
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onRoomConnectFromMenu(RtypeProtocol::RoomConnection)
{
  // Send data informing connection to a room
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onUserReadyFromMenu(RtypeProtocol::User)
{
  // Send signal data notifying user ready
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onUserMessageFromMenu(RtypeProtocol::Message)
{
  // Send user message
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onCreateRoomFromMenu(RtypeProtocol::Room room)
{
  RtypeProtocol::Header header;
  char			buffer[sizeof(header) + sizeof(room)];

  std::cout << __FUNCTION__ << std::endl;
  header.type = RtypeProtocol::T_ROOM_CREATE;
  header.data_size = sizeof(room);
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &room, sizeof(room));
  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(room));
  return (true);
}
