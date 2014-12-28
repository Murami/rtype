#include "Game/EntityEventReceiver.hh"

namespace Game
{
  void	EntityEventReceiver::dispatch(const Entity& entity, const EntityEvent& event)
  {
    event.dispatch(entity, *this);
  }

  void	EntityEventReceiver::update(const Entity& entity, const EntityEvent& event)
  {
    dispatch(entity, event);
  }
};
