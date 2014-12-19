#include "Game/EntityEventMove.hh"
#include "Game/EntityEventReceiver.hh"

namespace Game
{
  EntityEvent::Move::Move(const Util::Vec2& p_position)
  {
    position = p_position;
  }

  EntityEvent::Move::~Move()
  {
  }

  void	EntityEvent::Move::dispatch(const Entity& entity, EntityEventReceiver& receiver) const
  {
    receiver.receive(entity, *this);
  }
};
