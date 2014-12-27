#ifndef GAME_CORE_EVENT_SPAWN
#define GAME_CORE_EVENT_SPAWN

#include "Game/CoreEvent.hh"

namespace Game
{
  class Entity;

  class CoreEvent::Spawn : public CoreEvent
  {
  public:
    Entity&	entity;

  public:
    Spawn(Entity& p_entity);
    virtual ~Spawn() {}

    void	dispatch(const Core& core, CoreEventReceiver& receiver) const;
  };
};

#endif /* GAME_CORE_EVENT_SPAWN */
