#ifndef GAME_CORE_EVENT_SPAWN
#define GAME_CORE_EVENT_SPAWN

#include "Game/CoreEvent.hh"

namespace Game
{
  class Entity;

  class CoreEvent::Spawn
  {
  public:
    Entity&	entity;

  public:
    Spawn(Entity& p_entity);
    ~Spawn();
  };
};

#endif /* GAME_CORE_EVENT_SPAWN */
