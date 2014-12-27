#ifndef GAME_CORE_EVENT_RECEIVER
#define GAME_CORE_EVENT_RECEIVER

#include "Util/Observer.hpp"
#include "Game/CoreEvent.hh"

namespace Game
{
  class Core;

  class CoreEventReceiver : public Util::Observer<Core, CoreEvent>
  {
  public:
    virtual ~CoreEventReceiver() {}

    void		dispatch(const Core& core, const CoreEvent& event);
    void		update(const Core& core, const CoreEvent& event);

    virtual void		receive(const Core& core, const CoreEvent::Spawn& event) = 0;
    virtual void		receive(const Core& core, const CoreEvent::Destroy& event) = 0;
  };
};

#endif /* GAME_CORE_EVENT_RECEIVER */
