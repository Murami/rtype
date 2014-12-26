
#ifndef _IGAME_LISTENER_HH_
# define _IGAME_LISTENER_HH_

# include	"GameEnum.hh"

class	IGameListener
{
public:
  virtual ~IGameListener() {}
  virtual void	onKeyEvent(std::size_t) = 0;
};

#endif
