#ifndef		__RTYPECLIENT_HH__
# define	__RTYPECLIENT_HH__

# include	<SFML/Graphics.hpp>
# include	"IMenuListener.hh"
# include	"ConnectionConfiguration.hh"
# include	"INetworkListener.hh"

class		MenuController;
class		MenuView;
class		TcpConnection;
class		GameView;
class		GameController;

class		RtypeClient : public IMenuListener,
			      public INetworkListener
{
private:
  ConnectionConfiguration	_configuration;
  TcpConnection*		_tcpConnection;
  MenuController*		_menuController;
  MenuView*			_menuView;
  GameController*		_gameController;
  GameView*			_gameView;
  sf::RenderWindow*		_window;

  // INetworkListener
public:
  virtual void	onMagic(Network::Magic);
  virtual void	onConnection();
  virtual void	onDisconnection();
  virtual void	onRoomInfo(Network::Room);
  virtual void	onPingPong(Network::PingPong);
  virtual void	onGameStart();
  virtual void	onGameEnd(Network::EndGame);
  virtual void	onScore(Network::Score);
  virtual void	onMessage(Network::Message);

  // IMenuListener
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
