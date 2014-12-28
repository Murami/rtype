#ifndef GAME_CORE
#define GAME_CORE

#include "Util/Observable.hpp"
#include "Physic/World.hh"
#include "Util/PluginLoader.hpp"

namespace Game
{
  class CoreEvent;
  class Entity;
  class Player;
  class	Monster;

  class Core : public Util::Observable<Core, CoreEvent>
  {
  public:
    std::list<Entity*>		_entities;
    Physic::World		_world;
    bool			_alive;
    unsigned int		_playercount;
    PluginLoader<Monster>	_loader;

  public:
    Core();
    ~Core();

    bool		alive() const;

    void		update(float time);
    Physic::World&	getWorld();

    Player&		addPlayer();
    Entity*		getEntity(unsigned int);
    void		deleteEntity(Entity*);
    void		addMissile(const Player& player);
    void		spawnMonster();
  };
};

#endif /* GAME_CORE */
