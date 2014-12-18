#ifndef PHYSIC_BODY
#define PHYSIC_BODY

#include "Util/Vec2.hh"
#include "Util/Observable.hpp"

namespace Physic
{
  class World;
  class BodyEvent;

  class Body : public Util::Observable<Body, BodyEvent>
  {
  private:
    Util::Vec2	_speed;
    Util::Vec2	_position;
    Util::Vec2	_size;
    World&	_world;

  public:
    Body(World& world);
    virtual ~Body();

    void		setSpeed(const Util::Vec2& speed);
    const Util::Vec2&	getSpeed() const;

    void		setPosition(const Util::Vec2& position);
    const Util::Vec2&	getPosition() const;

    void		setSize(const Util::Vec2& size);
    const Util::Vec2&	getSize() const;

    void		update(float time);
    bool		collide(const Body& body);

  private:
    void		notifyMove();
  };
};

#endif /* PHYSIC_BODY */
