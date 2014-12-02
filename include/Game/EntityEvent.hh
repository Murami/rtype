#ifndef GAME_ENTITY_EVENT
#define GAME_ENTITY_EVENT

namespace Game
{
  class Entity;
  class EntityEventReceiver;

  class EntityEvent
  {
    virtual ~EntityEvent();

    virtual void	dispatch(const Entity& entity, EntityEventReceiver& receiver) const = 0;
  };
};

#endif /* GAME_ENTITY_EVENT */
