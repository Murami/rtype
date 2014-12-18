#include "Game/CoreEventDestroy.hh"

namespace Game
{
  CoreEvent::Destroy::Destroy(Entity& entity) :
    _entity(entity)
  {
  }

  CoreEvent::Destroy::~Destroy()
  {
  }
};
