#ifndef		__NETWORKREADER__HH__
# define	__NETWORKREADER__HH__

# include	"Thread.hpp"
# include	"RtypeProtocol.hh"

class		INetworkListener;
class		TcpConnection;

class		NetworkReader : public Util::Thread<void>
{
public:
  static const int	BUFFER_SIZE;

private:
  TcpConnection&	_tcpConnection;
  RtypeProtocol::Type	_expectedPacket;
  INetworkListener*	_tcpListener;

public:
  NetworkReader(TcpConnection& tcpConnection);
  ~NetworkReader();

  int			run();

  void			setTcpListener(INetworkListener*);

  void			setExpectedPacket(RtypeProtocol::Type packetType);
  RtypeProtocol::Type	getExpectedPacket();

  void			onReadData(void *data, std::size_t size);
};

#endif
