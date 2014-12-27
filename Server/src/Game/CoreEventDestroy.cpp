#include "Game/CoreEventDestroy.hh"

namespace Game
{
  CoreEvent::Destroy::Destroy(Entity& p_entity) :
    entity(p_entity)
  {
  }

  CoreEvent::Destroy::~Destroy()
  {
  }
};
