#ifndef PHYSIC_WORLD_EVENT_RECEIVER
#define PHYSIC_WORLD_EVENT_RECEIVER

#include "Util/Observer.hpp"

namespace Physic
{
  class World;
  class WorldEvent;

  class WorldEventReceiver : public Util::Observer<World, WorldEvent>
  {
  public:
    virtual ~WorldEventReceiver();

    void		dispatch(const World& world, const WorldEvent& event);
    void		update(const World& world, const WorldEvent& event);

    virtual void	onCollide(const World& world, const WorldEvent::Collide& event) = 0;
  };
};

#endif /* PHYSIC_WORLD_EVENT */
