#include "Physic/BodyEventReceiver.hh"
#include "Util/Observable.hpp"

namespace Physic
{
  void	BodyEventReceiver::dispatch(const Physic::Body& body, const BodyEvent& event)
  {
    event.dispatch(body, *this);
  }

  void	BodyEventReceiver::update(const Physic::Body& body, const BodyEvent& event)
  {
    dispatch(body, event);
  }
};
