#ifndef GAME_CORE
#define GAME_CORE

namespace Game
{
  class CoreEvent;

  class Core : public Observable<Core, CoreEvent>,
  {
  };
};

#endif /* GAME_CORE */
