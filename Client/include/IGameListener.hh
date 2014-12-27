
#ifndef _IGAME_LISTENER_HH_
# define _IGAME_LISTENER_HH_

# include	<stdint.h>
# include	"GameEnum.hh"

class	IGameListener
{
public:
  virtual ~IGameListener() {}
  virtual void	onKeyEvent(uint32_t) = 0;
};

#endif
