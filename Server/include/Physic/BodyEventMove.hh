#ifndef PHYSIC_BODY_EVENT_MOVE
#define PHYSIC_BODY_EVENT_MOVE

#include "Physic/BodyEvent.hh"

namespace Physic
{
  class	BodyEvent::Move : public BodyEvent
  {
  private:
    Util::Vec2	_position;

  public:
    Move(const Util::Vec2& position);
    virtual ~Move();

    void		dispatch(const Body& body, BodyEventReceiver& receiver) const;

    const Util::Vec2&	getPosition() const;
  };
};

#endif /* PHYSIC_BODY_EVENT_MOVE */
