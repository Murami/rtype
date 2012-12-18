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
  virtual void	onMagic(RtypeProtocol::Magic);
  virtual void	onConnection();
  virtual void	onDisconnection();
  virtual void	onRoomInfo(RtypeProtocol::Room);
  virtual void	onPingPong(RtypeProtocol::PingPong);
  virtual void	onGameStart();
  virtual void	onGameEnd(RtypeProtocol::EndGame);
  virtual void	onScore(RtypeProtocol::Score);
  virtual void	onMessage(RtypeProtocol::Message);

  // IMenuListener
public:
  virtual bool	onConnectFromMenu(const std::string&);
  virtual bool	onDisconnectFromMenu();
  virtual bool	onRoomConnectFromMenu(RtypeProtocol::RoomConnection);
  virtual bool	onUserReadyFromMenu(RtypeProtocol::User);
  virtual bool	onUserMessageFromMenu(RtypeProtocol::Message);

public:
  void		run();

public:
  RtypeClient();
  virtual ~RtypeClient();
};

#endif
