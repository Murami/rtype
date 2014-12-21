#ifndef		__TCPNETWORKREADER__HH__
# define	__TCPNETWORKREADER__HH__

# include	<deque>

# include	"Thread.hpp"
# include	"RtypeProtocol.hh"
# include	"Mutex.hh"

class		ITcpNetworkListener;
class		TcpConnection;

class		TcpNetworkReader : public Util::Thread<Util::Mutex*>
{
private:
  TcpConnection&	_tcpConnection;
  RtypeProtocol::Type	_expectedPacket;
  size_t		_expectedSize;
  ITcpNetworkListener*	_tcpListener;
  std::deque<char>	_buffer;
  Util::Mutex*		_mutex;

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
};

#endif
