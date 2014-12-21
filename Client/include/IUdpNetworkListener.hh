#ifndef __IUDPNETWORK_LISTENER_HH__
# define __IUDPNETWORK_LISTENER_HH__

#include "RtypeProtocol.hh"

class IUdpNetworkListener
{
public:
  virtual void	onPlayerInfo() = 0;
  virtual void	onPosition() = 0;
  virtual void	onSpawn() = 0;
  virtual void	onDestruction() = 0;
  virtual void	onLife() = 0;
  virtual void	onBonus() = 0;
  virtual void	onHit() = 0;
  virtual void	onDeath() = 0;
  virtual void	onEntityInfo() = 0;
};

#endif
