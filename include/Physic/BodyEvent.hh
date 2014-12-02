#ifndef PHYSIC_BODY_EVENT
#define PHYSIC_BODY_EVENT

#include "Util/Vec2.hh"

namespace Physic
{
  class BodyEventReceiver;
  class Body;

  class BodyEvent
  {
  public:
    class Move;

  public:
    virtual ~BodyEvent() {};

    virtual void	dispatch(const Body& body, BodyEventReceiver& receiver) const = 0;
  };
};

#endif /* PHYSIC_BODY_EVENT */
