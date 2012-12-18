#ifndef		__INETWORK_LISTENER_HH__
# define	__INETWORK_LISTENER_HH__

# include	"RtypeProtocol.hh"

class		INetworkListener
{
public:
  virtual void	onMagic(RtypeProtocol::Magic) = 0;
  virtual void	onConnection() = 0;
  virtual void	onDisconnection() = 0;
  virtual void	onRoomInfo(RtypeProtocol::Room) = 0;
  virtual void	onPingPong(RtypeProtocol::PingPong) = 0;
  virtual void	onGameStart() = 0;
  virtual void	onGameEnd(RtypeProtocol::EndGame) = 0;
  virtual void	onScore(RtypeProtocol::Score) = 0;
  virtual void	onMessage(RtypeProtocol::Message) = 0;
};

#endif
