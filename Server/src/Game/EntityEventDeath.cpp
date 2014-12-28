#include "Game/EntityEventReceiver.hh"
#include "Game/EntityEventDeath.hh"

namespace Game
{
  void	EntityEvent::Death::dispatch(const Entity& entity, EntityEventReceiver& receiver) const
  {
    receiver.receive(entity, *this);
  }
};
