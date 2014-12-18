#include "Game/CoreEventReceiver.hh"

namespace Game
{
  void	CoreEventReceiver::dispatch(const Core& core, const CoreEvent& event)
  {
    event.dispatch(core, *this);
  }

  void	CoreEventReceiver::update(const Core& core, const CoreEvent& event)
  {
    dispatch(core, event);
  }
};
