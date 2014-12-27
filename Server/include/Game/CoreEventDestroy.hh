#ifndef GAME_CORE_EVENT_DESTROY
#define GAME_CORE_EVENT_DESTROY

#include "Game/CoreEvent.hh"

namespace Game
{
  class Entity;

  class CoreEvent::Destroy
  {
  public:
    Entity&	entity;

  public:
    Destroy(Entity& p_entity);
    ~Destroy();
  };
};

#endif /* GAME_CORE_EVENT_DESTROY */
