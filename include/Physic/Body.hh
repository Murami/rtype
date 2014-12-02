#ifndef PHYSIC_BODY
#define PHYSIC_BODY

#include "Util/Vec2.hh"
#include "Util/Observable.hpp"
#include "Physic/WorldBody.hh"

namespace Physic
{
  class World;
  class BodyEvent;

  class Body : public Util::Observable<Body, BodyEvent>,
	       public WorldBody
  {
  private:
    Util::Vec2	_speed;
    Util::Vec2	_position;
    World&	_world;

  public:
    Body(World& world);
    virtual ~Body();

    void	setSpeed(Util::Vec2& speed);
    Util::Vec2&	getSpeed();

    void	setPosition(Util::Vec2& position);
    Util::Vec2&	getPosition();

  private:
    void	update(float time);
    void	notifyMove();
  };
};

#endif /* PHYSIC_BODY */
