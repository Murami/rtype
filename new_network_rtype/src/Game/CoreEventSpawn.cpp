#include "Game/CoreEventSpawn.hh"

namespace Game
{
  CoreEvent::Spawn::Spawn(Entity& entity) :
    _entity(entity)
  {
  }

  CoreEvent::Spawn::~Spawn()
  {
  }
};
