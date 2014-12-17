#ifndef		__NETWORKREADER__HH__
# define	__NETWORKREADER__HH__

# include	"RtypeProtocol.hh"

class		INetworkListener;
class		TcpConnection;

class		NetworkReader
{
public:
  static const int	BUFFER_SIZE;

private:
  TcpConnection&	_tcpConnection;
  Network::Type		_expectedPacket;
  INetworkListener*	_tcpListener;

public:
  NetworkReader(TcpConnection& tcpConnection);
  ~NetworkReader();

  void		setTcpListener(INetworkListener*);

  void		setExpectedPacket(Network::Type packetType);
  Network::Type	getExpectedPacket();

  void		start();
  void		onReadData(void *data, std::size_t size);
};

#endif
