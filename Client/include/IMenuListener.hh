#ifndef		__IMENULISTENER_HH__
# define	__IMENULISTENER_HH__

# include	<string>
# include	"RtypeProtocol.hh"

class		IMenuListener
{
public:
  virtual bool	onConnect(const std::string&) = 0;
  virtual bool	onDisconnect() = 0;
  virtual bool	onRoomConnect(Network::RoomConnection) = 0;
  virtual bool	onUserReady(Network::User) = 0;
  virtual bool	onUserMessage(Network::Message) = 0;

public:
  virtual	~IMenuListener() {}
};

#endif
