#ifndef PHYSIC_WORLD_EVENT
#define PHYSIC_WORLD_EVENT

namespace Physic
{
  class World;
  class WorldEventReceiver;

  class WorldEvent
  {
  public:
    class Collide;

  public:
    virtual ~WorldEvent() {}

    virtual void	dispatch(const World& world, WorldEventReceiver& receiver) const = 0;
  };
};

#endif /* PHYSIC_WORLD_EVENT */
