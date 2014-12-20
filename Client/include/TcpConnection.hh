#ifndef		__TCPCONNECTION_HH__
# define	__TCPCONNECTION_HH__

# include	<SFML/Network.hpp>

# include	"NetworkWriter.hh"
# include	"NetworkReader.hh"

class		ConnectionConfiguration;

class		TcpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::TcpSocket				_socket;
  NetworkReader*			_reader;
  NetworkWriter*			_writer;
  bool					_reading;

public:
  TcpConnection(const ConnectionConfiguration&);
  ~TcpConnection();

  bool			connect();
  bool			write(const void *data, std::size_t count);

  void			startRead();
  void			joinRead();
  void			stopRead();
  bool			isReading() const;

  sf::TcpSocket&	socket();
};

#endif
