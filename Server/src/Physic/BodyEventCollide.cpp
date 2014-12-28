#include "Physic/BodyEventCollide.hh"
#include "Physic/BodyEventReceiver.hh"

namespace Physic
{
  BodyEvent::Collide::Collide(Body& body) :
    _body(body)
  {
  }

  BodyEvent::Collide::~Collide()
  {
  }

  void	BodyEvent::Collide::dispatch(const Body& world, BodyEventReceiver& receiver) const
  {
    receiver.receive(world, *this);
  }

  Body&	BodyEvent::Collide::getBody() const
  {
    return (_body);
  }
};
