#ifndef GAME_CORE
#define GAME_CORE

#include "Util/Observable.hpp"
#include "Physic/World.hh"

namespace Game
{
  class CoreEvent;
  class Entity;
  class Player;

  class Core : public Util::Observable<Core, CoreEvent>
  {
  public:
    std::list<Entity*>	_entities;
    Physic::World	_world;
    bool		_alive;

  public:
    Core();
    ~Core();

    bool		alive() const;

    void		update(float time);
    Physic::World&	getWorld();

    Player&		addPlayer();
  };
};

#endif /* GAME_CORE */