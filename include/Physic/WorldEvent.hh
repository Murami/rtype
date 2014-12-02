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
    virtual ~WorldEvent();

    virtual void	dispatch(const World& world, WorldEventReceiver& receiver) const = 0;
  };

  class WorldEvent::Collide : public WorldEvent
  {
  private:
    const Body&	_body1;
    const Body&	_body2;

  public:
    Collide(const Body& body1, const Body& body2);
    ~Collide();

    void	dispatch(const World& world, WorldEventReceiver& receiver) const;

    const Body&	getFirstBody() const;
    const Body&	getSecondBody() const;
  };
};

#endif /* PHYSIC_WORLD_EVENT */
