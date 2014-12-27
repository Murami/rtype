#ifndef		__ITCPNETWORK_LISTENER_HH__
# define	__ITCPNETWORK_LISTENER_HH__

# include	"RtypeProtocol.hh"

class		ITcpNetworkListener
{
public:
  virtual void	onMagicBadVersion() = 0;
  virtual void	onMagicAccept() = 0;
  virtual void	onConnectionAlreadyConnected() = 0;
  virtual void	onConnectionInternalError() = 0;
  virtual void	onConnectionOk() = 0;
  virtual void	onDisconnection() = 0;
  virtual void	onRoomInfo(RtypeProtocol::Room) = 0;
  virtual void	onRoomCreateAlreadyExist(RtypeProtocol::Room) = 0;
  virtual void	onRoomCreateInternalError(RtypeProtocol::Room) = 0;
  virtual void	onRoomCreateOk(RtypeProtocol::Room) = 0;
  virtual void	onRoomJoinNotFound(RtypeProtocol::Room) = 0;
  virtual void	onRoomJoinIsFull(RtypeProtocol::Room) = 0;
  virtual void	onRoomJoinBadPswd(RtypeProtocol::Room) = 0;
  virtual void	onRoomJoinOk(RtypeProtocol::Room) = 0;
  virtual void	onRoomExitOk(RtypeProtocol::Room) = 0;
  virtual void	onPing(RtypeProtocol::PingPong) = 0;
  virtual void	onGameStart() = 0;
  virtual void	onGameEnd(RtypeProtocol::EndGame) = 0;
  virtual void	onScore(RtypeProtocol::Score) = 0;
  virtual void	onMessage(RtypeProtocol::Message) = 0;
  virtual void	onHostLeftRoom() = 0;
  virtual void	onDeleteRoom(RtypeProtocol::Room) = 0;
};

#endif
