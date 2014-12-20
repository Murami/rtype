#ifndef		__NETWORKWRITER_HH__
# define	__NETWORKWRITER_HH__

# include	<deque>

# include	"Mutex.hh"
# include	"Thread.hpp"
# include	"RtypeProtocol.hh"

class		TcpConnection;

class		NetworkWriter : public Util::Thread<void>
{
private:
  TcpConnection&	_tcpConnection;
  std::deque<char>	_buffer;
  Util::Mutex		_mutex;
  Util::Mutex		_cond;

public:
  NetworkWriter(TcpConnection& connection);
  ~NetworkWriter();

  int			run();
  void			sendData(void *data, std::size_t size);
};

#endif
