#ifndef		__IMENULISTENER_HH__
# define	__IMENULISTENER_HH__

# include	<string>
# include	"RtypeProtocol.hh"

class		IMenuListener
{
public:
  virtual bool	onConnectFromMenu(const std::string&) = 0;
  virtual bool	onDisconnectFromMenu() = 0;
  virtual bool	onRoomConnectFromMenu(Network::RoomConnection) = 0;
  virtual bool	onUserReadyFromMenu(Network::User) = 0;
  virtual bool	onUserMessageFromMenu(Network::Message) = 0;

public:
  virtual	~IMenuListener() {}
};

#endif
