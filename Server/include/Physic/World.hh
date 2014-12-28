#ifndef PHYSIC_WORLD
#define PHYSIC_WORLD

#include <list>
#include "Physic/BodyContainer.hh"

namespace Physic
{
  class WorldEvent;

  class World : public BodyContainer
  {
  private:
    std::list<Body*>	_bodies;
    std::list<Body*>	_bodies2;

  public:
    World();
    ~World();

    void	update(float time);

  private:
    void	add(Body& body);
    void	remove(Body& body);
  };
};

#endif /* PHYSIC_WORLD */
