#include "Physic/World.hh"

namespace Physic
{
  World::World()
  {
  }

  World::~World()
  {
  }

  void	World::update(float /*time*/)
  {
  }

  void	World::add(Body& body)
  {
    _bodies.push_back(&body);
  }

  void	World::remove(Body& body)
  {
    _bodies.remove(&body);
  }
};
