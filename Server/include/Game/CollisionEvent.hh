#ifndef GAME_COLLISION_EVENT
#define GAME_COLLISION_EVENT

#include "Physic/BodyEvent.hh"
#include "Physic/BodyEventReceiver.hh"

namespace Game
{
  class Entity;
  class Body;
  class CollisionReceiver;

  class CollisionEvent : public Physic::BodyEvent
  {
  private:
    Entity&	_entity;

  public:
    CollisionEvent(Entity& entity);
    ~CollisionEvent();

    void	dispatch(const Physic::Body& body, Physic::BodyEventReceiver& receiver) const;
    void	dispatch(const Physic::Body& body, CollisionReceiver& receiver) const;
  };
};

#endif /* GAME_COLLISION_EVENT */
