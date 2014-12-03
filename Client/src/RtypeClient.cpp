#include	"MenuController.h"
#include	"MenuView.h"
#include	"TcpConnection.hh"
#include	"RtypeClient.hh"

RtypeClient::RtypeClient()
{
  _tcpConnection = new TcpConnection(_configuration);
}

bool	RtypeClient::onConnect(const std::string & login)
{
  // Send connection datas
  std::cout << __FUNCTION__ << " : " << login << std::endl;
  return (true);
}

bool	RtypeClient::onDisconnect()
{
  // Send disconnection datas
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onRoomConnect(Network::RoomConnection)
{
  // Send data informing connection to a room
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onUserReady(Network::User)
{
  // Send signal data notifying user ready
  std::cout << __FUNCTION__ << std::endl;
  return (true);
}

bool	RtypeClient::onUserMessage(Network::Message)
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
