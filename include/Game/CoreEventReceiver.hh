#ifndef GAME_CORE_EVENT_RECEIVER
#define GAME_CORE_EVENT_RECEIVER

#include "Util/Observer.hpp"

namespace Game
{
  class Core;
  class CoreEvent;
  class CoreSpawnEvent;
  class CoreDeleteEvent;

  class CoreEventReceiver : public Util::Observer<Core, CoreEvent>
  {
  public:
    CoreEventReceiver();
    virtual ~CoreEventReceiver();

    void		dispatch(const Core& core, const CoreEvent& event);
    void		update(const Core& core, const CoreEvent& event);

    virtual void	onSpawn(const Core& core, const CoreSpawnEvent& event) = 0;
    virtual void	onDelete(const Core& core, const CoreDeleteEvent& event) = 0;
  };
};

#endif /* GAME_CORE_EVENT_RECEIVER */
