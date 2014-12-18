#ifndef GAME_CORE_EVENT_SPAWN
#define GAME_CORE_EVENT_SPAWN

#include "Game/CoreEvent.hh"

namespace Game
{
  class Entity;

  class CoreEvent::Spawn
  {
  public:
    Entity&	_entity;

  public:
    Spawn(Entity& entity);
    ~Spawn();
  };
};

#endif /* GAME_CORE_EVENT_SPAWN */
