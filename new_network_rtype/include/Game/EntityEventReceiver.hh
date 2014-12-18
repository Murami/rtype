#ifndef ENTITY_EVENT_RECEIVER
#define ENTITY_EVENT_RECEIVER

#include "Util/Observer.hpp"
#include "Game/EntityEvent.hh"
#include "Game/EntityEventMove.hh"
#include "Game/EntityEventLife.hh"

namespace Game
{
  class Entity;

  class EntityEventReceiver : public Util::Observer<Entity, EntityEvent>
  {
  public:
    virtual ~EntityEventReceiver() {}

    void		dispatch(const Entity& entity, const EntityEvent& event);
    void		update(const Entity& entity, const EntityEvent& event);

    virtual void	receive(const Entity& entity, const EntityEvent::Move& event) = 0;
    virtual void	receive(const Entity& entity, const EntityEvent::Life& event) = 0;
  };
};

#endif /* ENTITY_EVENT_RECEIVER */
