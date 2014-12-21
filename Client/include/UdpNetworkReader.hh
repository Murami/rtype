
#ifndef _UDP_NETWORK_READER_HH_
# define _UDP_NETWORK_READER_HH_

# include "Thread.hpp"
# include "Mutex.hh"

class	UdpNetworkReader : public Util::Thread<Util::Mutex*>
{
public:
  UdpNetworkReader();
  ~UdpNetworkReader();

private:

};

#endif /* _UDP_NETWORK_READER_HH_ */
