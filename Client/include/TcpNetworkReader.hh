#ifndef		__TCPNETWORKREADER__HH__
# define	__TCPNETWORKREADER__HH__

# include	<map>
# include	<deque>

# include	"Thread.hpp"
# include	"RtypeProtocol.hh"
# include	"Mutex.hh"

class		ITcpNetworkListener;
class		TcpConnection;

// typedef	void (ITcpNetworkListener::*)()	TcpCallback;

class		TcpNetworkReader : public Util::Thread<Util::Mutex*>
{
private:
  TcpConnection&				_tcpConnection;
  RtypeProtocol::Type				_expectedPacket;
  size_t					_expectedSize;
  ITcpNetworkListener*				_tcpListener;
  std::deque<char>				_buffer;
  Util::Mutex*					_mutex;
  //std::map<RtypeProtocol::Type, TcpCallback>	_callback;

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
  void			onReadRoom();
  void			onReadPing();

private:
  void		_changeExpectedData(RtypeProtocol::Type, std::size_t);
  void		_initCallbacks();
};

#endif
