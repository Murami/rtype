#ifndef GAME_CORE_EVENT_DESTROY
#define GAME_CORE_EVENT_DESTROY

#include "Game/CoreEvent.hh"

namespace Game
{
  class Entity;

  class CoreEvent::Destroy
  {
  private:
    Entity&	_entity;

  public:
    Destroy(Entity& entity);
    ~Destroy();
  };
};

#endif /* GAME_CORE_EVENT_DESTROY */
