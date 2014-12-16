#ifndef GAME_COLLISION_RECEIVER
#define GAME_COLLISION_RECEIVER

#include "Physic/BodyEventReceiver.hh"

namespace Game
{
  class CollisionEvent;

  class CollisionReceiver : public Physic::BodyEventReceiver
  {
  public:
    virtual	~CollisionReceiver() {}

    void		dispatch(const Physic::Body& body, const Physic::BodyEvent& event);
    void		update(const Physic::Body& body, const Physic::BodyEvent& event);

    virtual void	receive(const Physic::Body& body, const CollisionEvent& event) = 0;
    virtual void	receive(const Physic::Body& body, const Physic::BodyEvent::Move& event) = 0;
    virtual void	receive(const Physic::Body& body, const Physic::BodyEvent::Collide& collide) = 0;
  };
};

#endif /* GAME_COLLISION_RECEIVER */
