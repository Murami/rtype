#include "Physic/World.hh"
#include "Physic/Body.hh"
#include "Physic/BodyEvent.hh"
#include "Physic/BodyEventCollide.hh"

namespace Physic
{
  World::World()
  {
  }

  World::~World()
  {
  }

  void	World::update(float time)
  {
    std::list<Body*>::iterator	it;
    std::list<Body*>::iterator	it2;

    for (it = _bodies.begin(); it != _bodies.end(); it++)
      (*it)->update(time);

    for (it = _bodies.begin(); it != _bodies.end(); it++)
      for (it2 = std::next(it); it != _bodies.end(); it++)
	{
	  if ((*it)->collide(*(*it2)))
	    {
	      BodyEvent::Collide	event(*(*it2));

	      (*it)->notifyObservers(event);
	    }
	}
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
