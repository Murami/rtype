#ifndef		__TCPCONNECTION_HH__
# define	__TCPCONNECTION_HH__

# include	<SFML/Network.hpp>

class		ConnectionConfiguration;

class		TcpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::TcpSocket				_socket;

public:
  TcpConnection(const ConnectionConfiguration&);
  ~TcpConnection();

  bool			connect();
  bool			write(const void *data, std::size_t count);

  sf::TcpSocket&	socket();
};

#endif
