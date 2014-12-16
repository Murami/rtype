#ifndef GAME_ENTITY_EVENT_MOVE
#define GAME_ENTITY_EVENT_MOVE

#include "Util/Vec2.hh"
#include "Game/EntityEvent.hh"

namespace Game
{
  class EntityEvent::Move
  {
  public:
    Util::Vec2	position;

  public:
    Move(const Util::Vec2& p_position);
    ~Move();

    void	dispatch(const Entity& entity, EntityEventReceiver& receiver) const;
  };
};

#endif /* GAME_ENTITY_EVENT_MOVE */
