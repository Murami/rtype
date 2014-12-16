#ifndef		__RTYPECLIENT_HH__
# define	__RTYPECLIENT_HH__

# include	<SFML/Graphics.hpp>
# include	"IMenuListener.hh"
# include	"ConnectionConfiguration.hh"
# include	"GameView.hh"
# include	"GameController.hh"

class		MenuController;
class		MenuView;
class		TcpConnection;
class		GameView;
class		GameController;

class		RtypeClient : public IMenuListener
{
private:
  ConnectionConfiguration	_configuration;
  TcpConnection*		_tcpConnection;
  MenuController*		_menuController;
  MenuView*			_menuView;
  RType::GameController*		_gameController;
  RType::GameView*			_gameView;
  sf::RenderWindow*		_window;

public:
  virtual bool	onConnectFromMenu(const std::string&);
  virtual bool	onDisconnectFromMenu();
  virtual bool	onRoomConnectFromMenu(Network::RoomConnection);
  virtual bool	onUserReadyFromMenu(Network::User);
  virtual bool	onUserMessageFromMenu(Network::Message);

public:
  void		run();

public:
  RtypeClient();
  virtual ~RtypeClient();
};

#endif
