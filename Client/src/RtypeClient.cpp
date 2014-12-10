#include	"MenuController.h"
#include	"MenuView.h"
#include	"TcpConnection.hh"
#include	"RtypeClient.hh"
#include	"SoundManager.hh"

RtypeClient::RtypeClient()
{
  _tcpConnection = new TcpConnection(_configuration);
}

bool	RtypeClient::onConnectFromMenu(const std::string & login)
{
  // Send connection datas
  RType::SoundManager::Play("bip");
  std::cout << __FUNCTION__ << " : " << login << std::endl;
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
					       sf::VideoMode::getDesktopMode().height),
				 "Rtype", sf::Style::Fullscreen);
  RType::SoundManager::Play("theme");
  _window->setKeyRepeatEnabled(false);
  _menuView = new MenuView(*_window);
  _menuController = new MenuController(*_menuView);
  _menuView->addObserver(_menuController);
  _menuController->setMenuListener(this);
  _menuView->run(*_window);
  std::cout << std::boolalpha << _tcpConnection->connect() << std::endl;
}

RtypeClient::~RtypeClient()
{
  delete _menuView;
  delete _menuController;
  delete _window;
}
