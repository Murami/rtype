#ifndef		__RTYPECLIENT_HH__
# define	__RTYPECLIENT_HH__

# include	<SFML/Graphics.hpp>
# include	"IMenuListener.hh"
# include	"ConnectionConfiguration.hh"

class		MenuController;
class		MenuView;
class		TcpConnection;

class		RtypeClient : public IMenuListener
{
private:
  ConnectionConfiguration	_configuration;
  TcpConnection*		_tcpConnection;
  MenuController*		_menuController;
  MenuView*			_menuView;
  sf::RenderWindow*		_window;

public:
  virtual bool	onConnect(const std::string&);
  virtual bool	onDisconnect();
  virtual bool	onRoomConnect(Network::RoomConnection);
  virtual bool	onUserReady(Network::User);
  virtual bool	onUserMessage(Network::Message);

public:
  void		run();

public:
  RtypeClient();
  virtual ~RtypeClient();
};

#endif
