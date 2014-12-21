
#ifndef _UDP_NETWORK_READER_HH_
# define _UDP_NETWORK_READER_HH_

# include "Thread.hpp"
# include "Mutex.hh"

class	UdpConnection;

class	UdpNetworkReader : public Util::Thread<Util::Mutex*>
{
public:
  UdpNetworkReader();
  ~UdpNetworkReader();

  int	run(Util::Mutex&);

private:
  // UdpConnection&	_udpConnection;
};

#endif /* _UDP_NETWORK_READER_HH_ */
