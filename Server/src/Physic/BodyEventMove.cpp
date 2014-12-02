#include "Physic/BodyEventReceiver.hh"
#include "Physic/BodyEvent.hh"

namespace Physic
{
  BodyEvent::Move::Move(const Util::Vec2& position) :
    _position(position)
  {
  }

  BodyEvent::Move::~Move()
  {
  }

  void			BodyEvent::Move::dispatch(const Body& body, BodyEventReceiver& receiver) const
  {
    receiver.onMove(body, *this);
  }

  const Util::Vec2&	BodyEvent::Move::getPosition() const
  {
    return (_position);
  }
};
