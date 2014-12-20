#ifndef		__NETWORKREADER__HH__
# define	__NETWORKREADER__HH__

# include	<deque>

# include	"Thread.hpp"
# include	"RtypeProtocol.hh"
# include	"Mutex.hh"

class		INetworkListener;
class		TcpConnection;

class		NetworkReader : public Util::Thread<Util::Mutex*>
{
private:
  TcpConnection&	_tcpConnection;
  RtypeProtocol::Type	_expectedPacket;
  INetworkListener*	_tcpListener;
  std::deque<char>	_buffer;
  Util::Mutex*		_mutex;

public:
  NetworkReader(TcpConnection& tcpConnection);
  ~NetworkReader();

  int			run(Util::Mutex*);

  void			setTcpListener(INetworkListener*);

  void			setExpectedPacket(RtypeProtocol::Type packetType);
  RtypeProtocol::Type	getExpectedPacket();

  void			onReadData(void *data, std::size_t size);
};

#endif
