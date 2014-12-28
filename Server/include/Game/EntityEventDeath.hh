#ifndef ENTITY_EVENT_DEATH
#define ENTITY_EVENT_DEATH

# include	"EntityEvent.hh"

namespace Game
{
  class EntityEvent::Death : public EntityEvent
  {
  public:
    Death() {}
    ~Death() {}

    void	dispatch(const Entity& entity, EntityEventReceiver& receiver) const;
  };
};

#endif /* DEATH */
