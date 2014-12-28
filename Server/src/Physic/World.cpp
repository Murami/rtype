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

    for (it = _bodies2.begin(); it != _bodies2.end(); it++)
      (*it)->update(time);


    for (it = _bodies.begin(); it != _bodies.end(); it++)
      {
	for (it2 = _bodies2.begin(); it2 != _bodies2.end(); it2++)
	  {
	    if ((*it)->collide(*(*it2)))
	      {
		BodyEvent::Collide	event(*(*it2));

		(*it)->notifyObservers(event);
	      }
	  }
      }
  }

  void	World::add(Body& body)
  {
    if (body.getGroup())
      _bodies.push_back(&body);
    else
      _bodies2.push_back(&body);
  }

  void	World::remove(Body& body)
  {
    if (body.getGroup())
      _bodies.remove(&body);
    else
      _bodies2.remove(&body);
  }
};
