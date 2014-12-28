#ifndef ENTITY_EVENT_DEATH
#define ENTITY_EVENT_DEATH

namespace Game
{
  class EntityEvent::Death : public EntityEvent
  {
    Death() {}
    ~Death() {}

    void	dispatch(const Entity& entity, EntityEventReceiver& receiver) const;
  };
};

#endif /* DEATH */
