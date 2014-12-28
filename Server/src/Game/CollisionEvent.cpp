#include "Game/CollisionEvent.hh"
#include "Game/CollisionReceiver.hh"
#include <iostream>

namespace Game
{
  CollisionEvent::CollisionEvent(Entity& entity) :
    _entity(entity)
  {
  }

  CollisionEvent::~CollisionEvent()
  {
  }

  void	CollisionEvent::dispatch(const Physic::Body& body, Physic::BodyEventReceiver& receiver) const
  {
    dispatch(body, static_cast<CollisionReceiver&>(receiver));
  }

  void	CollisionEvent::dispatch(const Physic::Body& body, CollisionReceiver& receiver) const
  {
    receiver.receive(body, *this);
  }
};
