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
  bool		connect();

public:
  TcpConnection(const ConnectionConfiguration&);
  ~TcpConnection();
};

#endif
