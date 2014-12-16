#include "Game/EntityEventLife.hh"
#include "Game/EntityEventReceiver.hh"

namespace Game
{
  EntityEvent::Life::Life(int p_life)
  {
    life = p_life;
  }

  EntityEvent::Life::~Life()
  {
  }

  void	EntityEvent::Life::dispatch(const Entity& entity, EntityEventReceiver& receiver) const
  {
    receiver.receive(entity, *this);
  }
};
