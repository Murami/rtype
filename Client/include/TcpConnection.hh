#ifndef		__TCPCONNECTION_HH__
# define	__TCPCONNECTION_HH__

# include	<thread>
# include	<SFML/Network.hpp>

//# include	"CircularBuffer.hh"

class		ConnectionConfiguration;

class		TcpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::TcpSocket				_socket;
  std::thread*				_readThread;
  //  CircularBuffer			_circularBuffer;

public:
  bool		connect();
  bool		write(const void *data, std::size_t count);
  void		startRead();

public:
  TcpConnection(const ConnectionConfiguration&);
  ~TcpConnection();
};

//static void	readOnSocket(CircularBuffer&, sf::TcpSocket&);

#endif
