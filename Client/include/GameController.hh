
#ifndef _GAME_CONTROLLER_HH_
# define _GAME_CONTROLLER_HH_

# include "IGameObserver.hh"
# include "IGameListener.hh"

class	GameView;

class	GameController : public IGameObserver
{
public:
  GameController(GameView&);
  ~GameController();

  void	update();

  void	setGameController(IGameListener*);

private:
  GameView&		_view;
  IGameListener*	_listener;
  /* mettre un network ici */
};

#endif
