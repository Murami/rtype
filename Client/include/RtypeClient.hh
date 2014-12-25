#ifndef		__RTYPECLIENT_HH__
# define	__RTYPECLIENT_HH__

# include	<SFML/Graphics.hpp>
# include	"IMenuListener.hh"
# include	"ConnectionConfiguration.hh"
# include	"ITcpNetworkListener.hh"
# include	"IUdpNetworkListener.hh"
# include	"IKeyListener.hh"
# include	"IGameListener.hh"
# include	"Mutex.hh"

class		MenuController;
class		MenuView;
class		TcpConnection;
class		UdpConnection;
class		GameView;
class		GameController;

class		RtypeClient :	public IMenuListener,
				public ITcpNetworkListener,
				public IUdpNetworkListener,
				public IKeyListener,
				public IGameListener
{
private:
  ConnectionConfiguration	_configuration;
  TcpConnection*		_tcpConnection;
  UdpConnection*		_udpConnection;
  MenuController*		_menuController;
  MenuView*			_menuView;
  GameController*		_gameController;
  GameView*			_gameView;
  sf::RenderWindow*		_window;
  Util::Mutex			_mutex;

  // IUdpNetworkListener
public:
  virtual void	onPlayerInfo();
  virtual void	onPosition();
  virtual void	onSpawn();
  virtual void	onDestruction();
  virtual void	onLife();
  virtual void	onBonus();
  virtual void	onHit();
  virtual void	onDeath();
  virtual void	onEntityInfo();

  //IKeyListener
public:
  virtual void	onKeyEvent(RtypeEvent::eKeyEvent);

  // ITcpNetworkListener
public:
  virtual void	onMagicBadVersion();
  virtual void	onMagicAccept();
  virtual void	onConnectionAlreadyConnected();
  virtual void	onConnectionInternalError();
  virtual void	onConnectionOk();
  virtual void	onDisconnection();
  virtual void	onRoomInfo(RtypeProtocol::Room);
  virtual void	onRoomCreateAlreadyExist(RtypeProtocol::Room);
  virtual void	onRoomCreateInternalError(RtypeProtocol::Room);
  virtual void	onRoomCreateOk(RtypeProtocol::Room);
  virtual void	onRoomJoinNotFound(RtypeProtocol::Room);
  virtual void	onRoomJoinIsFull(RtypeProtocol::Room);
  virtual void	onRoomJoinBadPswd(RtypeProtocol::Room);
  virtual void	onRoomJoinOk(RtypeProtocol::Room);
  virtual void	onRoomExitOk(RtypeProtocol::Room);
  virtual void	onPing(RtypeProtocol::PingPong);
  virtual void	onGameStart();
  virtual void	onGameEnd(RtypeProtocol::EndGame);
  virtual void	onScore(RtypeProtocol::Score);
  virtual void	onMessage(RtypeProtocol::Message);

  // IMenuListener
public:
  virtual bool	onConnectFromMenu(const std::string&);
  virtual bool	onDisconnectFromMenu();
  virtual bool	onRoomConnectFromMenu(int id, const std::string& pass);
  virtual bool	onRoomLeaveFromMenu();
  virtual bool	onUserReadyFromMenu();
  virtual bool	onUserMessageFromMenu(RtypeProtocol::Message);
  virtual bool	onCreateRoomFromMenu(const std::string&, const std::string&);

public:
  void		run();

public:
  RtypeClient();
  virtual ~RtypeClient();
};

#endif
