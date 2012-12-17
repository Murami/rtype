#ifndef		__INETWORK_LISTENER_HH__
# define	__INETWORK_LISTENER_HH__

# include	"RtypeProtocol.hh"

class		INetworkListener
{
public:
  virtual void	onMagic(Network::Magic) = 0;
  virtual void	onConnection() = 0;
  virtual void	onDisconnection() = 0;
  virtual void	onRoomInfo(Network::Room) = 0;
  virtual void	onPingPong(Network::PingPong) = 0;
  virtual void	onGameStart() = 0;
  virtual void	onGameEnd(Network::EndGame) = 0;
  virtual void	onScore(Network::Score) = 0;
  virtual void	onMessage(Network::Message) = 0;
};

#endif
