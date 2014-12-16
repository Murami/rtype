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
    CoreEventReceiver();
    virtual ~CoreEventReceiver();

    void		dispatch(const Core& core, const CoreEvent& event);
    void		update(const Core& core, const CoreEvent& event);
  };
};

#endif /* GAME_CORE_EVENT_RECEIVER */
