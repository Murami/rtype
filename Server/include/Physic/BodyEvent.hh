#ifndef PHYSIC_BODY_EVENT
#define PHYSIC_BODY_EVENT

#include "Util/Vec2.hh"

namespace Physic
{
  class Body;
  class BodyEventReceiver;

  class BodyEvent
  {
  public:
    class Move;
    class Collide;

  public:
    virtual ~BodyEvent() {};

    virtual void	dispatch(const Body& body, BodyEventReceiver& receiver) const = 0;
  };
};

#endif /* PHYSIC_BODY_EVENT */
