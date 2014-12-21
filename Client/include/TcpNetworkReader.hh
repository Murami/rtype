#ifndef		__TCPNETWORKREADER__HH__
# define	__TCPNETWORKREADER__HH__

# include	<map>
# include	<deque>

# include	"Thread.hpp"
# include	"RtypeProtocol.hh"
# include	"Mutex.hh"

class		ITcpNetworkListener;
class		TcpConnection;

class		TcpNetworkReader;

typedef		void (TcpNetworkReader::*TcpCallback)();

class		TcpNetworkReader : public Util::Thread<Util::Mutex*>
{
private:
  TcpConnection&				_tcpConnection;
  RtypeProtocol::Type				_expectedPacket;
  size_t					_expectedSize;
  ITcpNetworkListener*				_tcpListener;
  std::deque<char>				_buffer;
  Util::Mutex*					_mutex;
  std::map<RtypeProtocol::Type, TcpCallback>	_callback;

public:
  TcpNetworkReader(TcpConnection& tcpConnection);
  ~TcpNetworkReader();

  int			run(Util::Mutex*);

  void			setTcpListener(ITcpNetworkListener*);

  void			setExpectedPacket(RtypeProtocol::Type packetType);
  RtypeProtocol::Type	getExpectedPacket();

  void			setTcpNetworkListener(ITcpNetworkListener *listener);

private:
  void			onReadData();
  void			onReadHeader();

  void			onMagicBadVersion();
  void			onMagicAccept();
  void			onReadRoom();
  void			onReadPing();
  void			onReadConnectionAlreadyConnected();
  void			onReadConnectionInternalError();
  void			onReadConnectionOk();
  void			onReadRoomCreateAlreadyExist();
  void			onReadRoomCreateInternalError();
  void			onReadRoomCreateOk();
  void			onReadRoomJoinNotFound();
  void			onReadRoomJoinIsFull();
  void			onReadRoomJoinBadPswd();
  void			onReadRoomJoinOk();
  void			onReadMessage();
  void			onReadGameStart();
  void			onReadGameEnd();
  void			onReadScore();
  void			onReadPlayerInfo();

private:
  void		_changeExpectedData(RtypeProtocol::Type, std::size_t);
  void		_initCallbacks();
};

#endif
