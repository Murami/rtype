
#ifndef _UDP_NETWORK_WRITER_HH_
# define _UDP_NETWORK_WRITER_HH_

# include "Thread.hpp"

class	UdpConnection;

class	UdpNetworkWriter : public Util::Thread<void>
{
public:
  UdpNetworkWriter();
  ~UdpNetworkWriter();

  int	run();

private:
  // UdpConnection&	_udpConnection;
};

#endif /* _UDP_NETWORK_WRITER_HH_ */
