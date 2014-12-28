#ifndef PHYSIC_BODY_EVENT_COLLIDE
#define PHYSIC_BODY_EVENT_COLLIDE

#include "Physic/BodyEvent.hh"

namespace Physic
{
  class Body;

  class BodyEvent::Collide : public BodyEvent
  {
  private:
    Body&	_body;

  public:
    Collide(Body& body);
    ~Collide();

    void	dispatch(const Body& world, BodyEventReceiver& receiver) const;

    Body&	getBody() const;
  };
};

#endif /* PHYSIC_BODY_EVENT_COLLIDE */
