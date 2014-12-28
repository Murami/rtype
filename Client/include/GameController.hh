
#ifndef _GAME_CONTROLLER_HH_
# define _GAME_CONTROLLER_HH_

# include <list>
# include "IGameObserver.hh"
# include "IGameListener.hh"
# include "RtypeProtocol.hh"

class	GameView;

class	GameController : public IGameObserver
{
public:
  GameController(GameView&);
  ~GameController();

  void	updateSpawnList();
  void	update(size_t);
  void	onExit();

  void	setGameListener(IGameListener*);

  void	spawnEntity(RtypeProtocol::Spawn);
  void	createEntity(int id, RtypeProtocol::Entity);
  void	updateEntityPosition(int id, RtypeProtocol::Position);

private:
  GameView&				_view;
  IGameListener*			_listener;
  std::list<RtypeProtocol::Spawn>	_spawnList;
};

#endif
