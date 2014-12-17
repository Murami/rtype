#ifndef		__TCPCONNECTION_HH__
# define	__TCPCONNECTION_HH__

# include	<thread>
# include	<boost/asio.hpp>
# include	<SFML/Network.hpp>

class		ConnectionConfiguration;

class		TcpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::TcpSocket				_socket;

public:
  bool		connect();
  bool		write(const void *data, std::size_t count);

public:
  TcpConnection(const ConnectionConfiguration&);
  ~TcpConnection();
};

#endif
