#ifndef ENTITY_EVENT_RECEIVER
#define ENTITY_EVENT_RECEIVER

#include "Util/Observer.hpp"

namespace Game
{
  class Entity;
  class EntityEvent;
  class EntityLifeEvent;
  class EntityPositionEvent;

  class EntityEventReceiver : public Util::Observer<Entity, EntityEvent>
  {
  public:
    EntityEventReceiver():
    virtual ~EntityEventReceiver();

    void		dispatch(Entity& entity, const EntityEvent& event);
    void		update(Entity& entity, const EntityEvent& event);

    virtual void	receive(Entity& entity, const EntityPositionEvent& event) = 0;
    virtual void	receive(Entity& entity, const EntityLifeEvent& event) = 0;
  };
};

#endif /* ENTITY_EVENT_RECEIVER */
