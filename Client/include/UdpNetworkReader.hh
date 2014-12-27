#ifndef _UDP_NETWORK_READER_HH_
# define _UDP_NETWORK_READER_HH_

# include <map>

# include "RtypeProtocol.hh"
# include "Thread.hpp"
# include "Mutex.hh"

class	IUdpNetworkListener;
class	UdpConnection;

class	UdpNetworkReader;

typedef	void (UdpNetworkReader::*callback)(char*);

class	UdpNetworkReader : public Util::Thread<Util::Mutex*>
{
private:
  UdpConnection&				_udpConnection;
  IUdpNetworkListener*				_listener;
  Util::Mutex*					_mutex;
  std::map<RtypeProtocol::Type, callback>	_callbacks;

public:
  UdpNetworkReader(UdpConnection&);
  ~UdpNetworkReader();

  int	run(Util::Mutex*);

  void	onReadData(char *);

  void	setUdpNetworkListener(IUdpNetworkListener*);

private:
  void	onReadMapChange(char *);
  void	onReadPlayerInfo(char *);
  void	onReadPosition(char *);
  void	onReadSpawn(char *);
  void	onReadEvent(char *);
  void	onReadDestruction(char *);
  void	onReadLife(char *);
  void	onReadBonus(char *);
  void	onReadHit(char *);
  void	onReadDeath(char *);
  void	onReadEntityInfos(char *);
};

#endif /* _UDP_NETWORK_READER_HH_ */
