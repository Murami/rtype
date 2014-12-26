
#ifndef _GAME_CONTROLLER_HH_
# define _GAME_CONTROLLER_HH_

# include "IGameObserver.hh"
# include "IGameListener.hh"
# include "RtypeProtocol.hh"

class	GameView;

class	GameController : public IGameObserver
{
public:
  GameController(GameView&);
  ~GameController();

  void	update(size_t);
  void	setGameListener(IGameListener*);

  void spawnEntity(int id, RtypeProtocol::Entity entity);
  void updateEntityPosition(int id, RtypeProtocol::Position);

private:
  GameView&		_view;
  IGameListener*	_listener;
};

#endif
