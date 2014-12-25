#ifndef _UDP_NETWORK_READER_HH_
# define _UDP_NETWORK_READER_HH_

# include "Thread.hpp"
# include "Mutex.hh"

class	IUdpNetworkListener;
class	UdpConnection;

class	UdpNetworkReader : public Util::Thread<Util::Mutex*>
{
private:
  UdpConnection&	_udpConnection;
  IUdpNetworkListener*	_listener;
  Util::Mutex*		_mutex;

public:
  UdpNetworkReader(UdpConnection&);
  ~UdpNetworkReader();

  int	run(Util::Mutex*);

  void	onReadData(char *);
  void	setUdpNetworkListener(IUdpNetworkListener*);
};

#endif /* _UDP_NETWORK_READER_HH_ */
