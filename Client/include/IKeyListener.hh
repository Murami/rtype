#ifndef		__IKEYLSITENER_HH__
# define	__IKEYLSITENER_HH__

# include	"GameEnum.hh"

class		IKeyListener
{
public:
  virtual void	onKeyEvent(RtypeEvent::eKeyEvent) = 0;
};

#endif
