#ifndef GAME_CORE_EVENT
#define GAME_CORE_EVENT

namespace Game
{
  class Core;
  class CoreEventReceiver;

  class CoreEvent
  {
  public:
    virtual ~CoreEvent();

    virtual void	dispatch(const Core& core, CoreEventReceiver& receveir) const = 0;
  };
};

#endif /* GAME_CORE_EVENT */
