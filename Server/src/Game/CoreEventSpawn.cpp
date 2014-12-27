#include "Game/CoreEventSpawn.hh"
#include "Game/CoreEventReceiver.hh"

namespace Game
{
  CoreEvent::Spawn::Spawn(Entity& p_entity) :
    entity(p_entity)
  {
  }

  void		CoreEvent::Spawn::dispatch(const Core& core, CoreEventReceiver& receiver) const
  {
    receiver.receive(core, *this);
  }

};
