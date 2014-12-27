#include "Game/CoreEventDestroy.hh"
#include "Game/CoreEventReceiver.hh"

namespace Game
{
  CoreEvent::Destroy::Destroy(Entity& p_entity) :
    entity(p_entity)
  {
  }

  void		CoreEvent::Destroy::dispatch(const Core& core, CoreEventReceiver& receiver) const
  {
    receiver.receive(core, *this);
  }
};
