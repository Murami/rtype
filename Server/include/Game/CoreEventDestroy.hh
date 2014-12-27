#ifndef GAME_CORE_EVENT_DESTROY
#define GAME_CORE_EVENT_DESTROY

#include "Game/CoreEvent.hh"

namespace Game
{
  class Entity;

  class CoreEvent::Destroy : public CoreEvent
  {
  public:
    Entity&	entity;

  public:
    Destroy(Entity& p_entity);
    ~Destroy() {}

    void	dispatch(const Core& core, CoreEventReceiver& receiver) const;
  };
};

#endif /* GAME_CORE_EVENT_DESTROY */
