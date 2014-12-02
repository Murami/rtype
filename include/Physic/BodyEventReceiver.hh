#ifndef PHYSIC_BODY_EVENT_RECEIVER
#define PHYSIC_BODY_EVENT_RECEIVER

#include "Util/Observer.hpp"
#include "Physic/BodyEvent.hh"
#include "Physic/BodyEventMove.hh"

namespace Physic
{
  class Body;

  class BodyEventReceiver : public Util::Observer<Body, BodyEvent>
  {
  public:
    virtual ~BodyEventReceiver() {};

    void		dispatch(const Body& body, const BodyEvent& event);
    void		update(const Body& body, const BodyEvent& event);

    virtual void	onMove(const Body&  body, const BodyEvent::Move& event) = 0;
  };
};

#endif /* PHYSIC_BODY_EVENT_RECEIVER */
