#ifndef		__TCPCONNECTION_HH__
# define	__TCPCONNECTION_HH__

# include	<SFML/Network.hpp>

# include	"TcpNetworkWriter.hh"
# include	"TcpNetworkReader.hh"

namespace	Util
{
  class		Mutex;
}

class		ITcpNetworkListener;
class		ConnectionConfiguration;

class		TcpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::TcpSocket				_socket;
  TcpNetworkReader*			_reader;
  TcpNetworkWriter*			_writer;
  bool					_reading;

public:
  TcpConnection(const ConnectionConfiguration&, Util::Mutex*);
  ~TcpConnection();

  bool			connect();
  bool			write(void *data, std::size_t count);

  void			startRead();
  void			joinRead();
  void			stopRead();
  bool			isReading() const;

  sf::TcpSocket&	socket();

  void			setTcpNetworkListener(ITcpNetworkListener *);
};

#endif
