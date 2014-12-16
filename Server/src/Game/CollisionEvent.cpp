#include "Game/CollisionEvent.hh"
#include "Game/CollisionReceiver.hh"

namespace Game
{
  CollisionEvent::CollisionEvent(Entity& entity) :
    _entity(entity)
  {
  }

  CollisionEvent::~CollisionEvent()
  {
  }

  void	CollisionEvent::dispatch(const Physic::Body& /*body*/, Physic::BodyEventReceiver& /*receiver*/) const
  {
    // DEAD END FOR EVENT SEND TO RECEVEIR THAT AREN'T ABLE TO TREAT IT
  }

  void	CollisionEvent::dispatch(const Physic::Body& body, CollisionReceiver& receiver) const
  {
    receiver.receive(body, *this);
  }
};
