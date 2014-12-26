
#ifndef _IGAME_LISTENER_HH_
# define _IGAME_LISTENER_HH_

# include	"GameEnum.hh"

class	IGameListener
{
public:
  virtual ~IGameListener() {}
  virtual void	onKeyEvent(RtypeEvent::eKeyEvent) = 0;
};

#endif
