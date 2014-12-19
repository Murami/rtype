#ifndef		__TCPCONNECTION_HH__
# define	__TCPCONNECTION_HH__

# include	<SFML/Network.hpp>

# include	"NetworkReader.hh"

class		ConnectionConfiguration;

class		TcpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::TcpSocket				_socket;
  NetworkReader*			_reader;
  bool					_running;

public:
  TcpConnection(const ConnectionConfiguration&);
  ~TcpConnection();

  bool			connect();
  bool			write(const void *data, std::size_t count);

  void			startRead();
  void			joinRead();
  void			stopRead();
  bool			isRunning() const;

  sf::TcpSocket&	socket();
};

#endif
