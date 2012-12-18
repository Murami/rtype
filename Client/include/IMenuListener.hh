#ifndef		__IMENULISTENER_HH__
# define	__IMENULISTENER_HH__

# include	<string>
# include	"RtypeProtocol.hh"

class		IMenuListener
{
public:
  virtual bool	onConnectFromMenu(const std::string&) = 0;
  virtual bool	onDisconnectFromMenu() = 0;
  virtual bool	onRoomConnectFromMenu(RtypeProtocol::RoomConnection) = 0;
  virtual bool	onUserReadyFromMenu(RtypeProtocol::User) = 0;
  virtual bool	onUserMessageFromMenu(RtypeProtocol::Message) = 0;

public:
  virtual	~IMenuListener() {}
};

#endif
