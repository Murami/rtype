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
  _tcpConnection = new TcpConnection(_configuration);
}

void	RtypeClient::onKeyEvent(RTypeEvent::eKeyEvent event)
{
  RtypeProtocol::Header header;

  header.type = RtypeProtocol::T_EVENT;
  header.data_size = sizeof(event);
  _tcpConnection->write(&header, sizeof(header));
  _tcpConnection->write(&event, sizeof(event));
}

void	RtypeClient::onMagic(RtypeProtocol::Magic)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onConnection()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onDisconnection()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onRoomInfo(RtypeProtocol::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onPingPong(RtypeProtocol::PingPong)
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

  SoundManager::Play("bip");
  std::cout << __FUNCTION__ << " : " << login << std::endl;
  header.type = RtypeProtocol::T_CONNECTION;
  header.data_size = sizeof(RtypeProtocol::User);
  strcpy(reinterpret_cast<char *>(&user.username[0]), login.c_str());
  _tcpConnection->write(&header,  sizeof(header));
  _tcpConnection->write(&user, sizeof(user));
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

void		RtypeClient::run()
{
  RtypeProtocol::Header header;
  RtypeProtocol::Magic	magic;

  _window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
					       sf::VideoMode::getDesktopMode().height), "Rtype");
  SoundManager::Play("scoring");

  _window->setKeyRepeatEnabled(false);
  _menuView = new MenuView(*_window);
  _menuController = new MenuController(*_menuView);
  if (!_tcpConnection->connect())
    throw (std::runtime_error("Connect"));

  _menuView->addObserver(_menuController);
  _menuController->setMenuListener(this);
  header.type = RtypeProtocol::T_MAGIC;
  header.data_size = sizeof(magic);
  magic.minor_version = htons(RtypeProtocol::minor_version);
  magic.major_version = htons(RtypeProtocol::major_version);
  std::memset(&magic.proto_name[0], 0, PROTO_NAME_SIZE);
  std::memcpy(reinterpret_cast<char *>(&magic.proto_name[0]),
	      RtypeProtocol::proto_name,
	      std::strlen(reinterpret_cast<const char *>(RtypeProtocol::proto_name)));

  char *buffer = new char[sizeof(header) + sizeof(magic)];
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &magic, sizeof(magic));

  _tcpConnection->startRead();

  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(magic));

  _menuView->run(*_window);
}

RtypeClient::~RtypeClient()
{
  delete _menuView;
  delete _menuController;
  delete _window;
}
