#ifndef		__IMENULISTENER_HH__
# define	__IMENULISTENER_HH__

# include	<string>
# include	"RtypeProtocol.hh"

class		IMenuListener
{
public:
  virtual bool	onConnectFromMenu(const std::string&) = 0;
  virtual bool	onDisconnectFromMenu() = 0;
  virtual bool	onRoomConnectFromMenu(int id, const std::string& pass) = 0;
  virtual bool	onRoomLeaveFromMenu() = 0;
  virtual bool	onUserReadyFromMenu(RtypeProtocol::User) = 0;
  virtual bool	onUserMessageFromMenu(RtypeProtocol::Message) = 0;
  virtual bool	onCreateRoomFromMenu(const std::string& roomName, const std::string& password) = 0;

public:
  virtual	~IMenuListener() {}
};

#endif
