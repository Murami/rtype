#ifndef GAME_ENTITY_EVENT_LIFE
#define GAME_ENTITY_EVENT_LIFE

#include "Game/EntityEvent.hh"

namespace Game
{
  class EntityEvent::Life
  {
  public:
    int		life;

  public:
    Life(int p_life);
    ~Life();

    void	dispatch(const Entity& entity, EntityEventReceiver& receiver) const;
  };
};

#endif /* GAME_ENTITY_EVENT_LIFE */
