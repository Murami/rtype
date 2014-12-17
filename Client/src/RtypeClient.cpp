#include	<stdexcept>

#include	"MenuController.h"
#include	"MenuView.h"
#include	"TcpConnection.hh"
#include	"RtypeClient.hh"
#include	"SoundManager.hh"
#include	"GameController.hh"
#include	"GameView.hh"

RtypeClient::RtypeClient()
{
  _tcpConnection = new TcpConnection(_configuration);
}

void	RtypeClient::onMagic(Network::Magic)
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

void	RtypeClient::onRoomInfo(Network::Room)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onPingPong(Network::PingPong)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onGameStart()
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onGameEnd(Network::EndGame)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onScore(Network::Score)
{
  std::cout << __FUNCTION__ << std::endl;
}

void	RtypeClient::onMessage(Network::Message)
{
  std::cout << __FUNCTION__ << std::endl;
}

bool	RtypeClient::onConnectFromMenu(const std::string & login)
{
  // Send connection datas
  RType::SoundManager::Play("bip");
  std::cout << __FUNCTION__ << " : " << login << std::endl;
  _tcpConnection->write(login.c_str(), login.size());
  return (true);
}

bool	RtypeClient::onDisconnectFromMenu()
{
  // Send disconnection datas
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onRoomConnectFromMenu(Network::RoomConnection)
{
  // Send data informing connection to a room
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onUserReadyFromMenu(Network::User)
{
  // Send signal data notifying user ready
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onUserMessageFromMenu(Network::Message)
{
  // Send user message
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

void		RtypeClient::run()
{
  _window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
					       sf::VideoMode::getDesktopMode().height), "Rtype");
  RType::SoundManager::Play("theme");
  // _window->setKeyRepeatEnabled(false);
  // _menuView = new MenuView(*_window);
  // _menuController = new MenuController(*_menuView);
  // if (!_tcpConnection->connect())
  //   throw (std::runtime_error("Connect"));
  // _menuView->addObserver(_menuController);
  // _menuController->setMenuListener(this);
  // _menuView->run(*_window);

  _gameView = new RType::GameView();
  _gameController = new RType::GameController(*_gameView);
  _gameView->addObserver(_gameController);
  _gameView->run(*_window);
}

RtypeClient::~RtypeClient()
{
  // delete _menuView;
  // delete _menuController;
  // delete _window;
}
