#include "Game/CollisionReceiver.hh"

namespace Game
{
  void	CollisionReceiver::dispatch(const Physic::Body& body, const Physic::BodyEvent& event)
  {
    event.dispatch(body, *this);
  }

  void	CollisionReceiver::update(const Physic::Body& body, const Physic::BodyEvent& event)
  {
    dispatch(body, event);
  }
};
