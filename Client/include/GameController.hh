
#ifndef _GAME_CONTROLLER_HH_
# define _GAME_CONTROLLER_HH_

# include "IGameObserver.hh"

class	GameView;

class	GameController : public IGameObserver
{
public:
  GameController(GameView&);
  ~GameController();

  void	update();

private:
  GameView&	_view;
  /* mettre un network ici */
};

#endif
