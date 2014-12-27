#ifndef _UDP_CONNECTION_HH_
# define _UDP_CONNECTION_HH_

# include	<SFML/Network.hpp>

# include	"UdpNetworkReader.hh"
# include	"UdpNetworkWriter.hh"

namespace	Util
{
  class		Mutex;
}

class	IUdpNetworkListener;
class	ConnectionConfiguration;

class	UdpConnection
{
private:
  const ConnectionConfiguration&	_conf;
  sf::UdpSocket				_socket;
  UdpNetworkReader*			_reader;
  UdpNetworkWriter*			_writer;
  bool					_reading;
  bool					_writing;
  IUdpNetworkListener*			_listener;

public:
  UdpConnection(const ConnectionConfiguration&, Util::Mutex*);
  ~UdpConnection();

  bool			connect();
  bool			write(void *data, std::size_t count);

  void			startRead();
  void			stopRead();
  void			joinRead();
  bool			isReading() const;

  void			setUdpNetworkListener(IUdpNetworkListener *);

  sf::UdpSocket&	socket();

  const std::string&	getIpFromConf() const;
  int			getPortFromConf() const;
  uint16_t		getLocalPort();
};

#endif /* _UDP_CONNECTION_HH_ */
