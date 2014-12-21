#ifndef		__TCPNETWORKWRITER_HH__
# define	__TCPNETWORKWRITER_HH__

# include	<deque>

# include	"Mutex.hh"
# include	"Thread.hpp"
# include	"RtypeProtocol.hh"

class		TcpConnection;

class		TcpNetworkWriter : public Util::Thread<void>
{
private:
  TcpConnection&	_tcpConnection;
  std::deque<char>	_buffer;
  Util::Mutex		_mutex;
  Util::Mutex		_cond;

public:
  TcpNetworkWriter(TcpConnection& connection);
  ~TcpNetworkWriter();

  int			run();
  void			sendData(void *data, std::size_t size);
};

#endif
