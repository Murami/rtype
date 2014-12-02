#include "Physic/Body.hh"
#include "Physic/BodyEvent.hh"
#include "Physic/BodyEventMove.hh"
#include "Physic/World.hh"

namespace Physic
{
  Body::Body(World& world) : _world(world)
  {
    _position = Util::Vec2(0, 0);
    _speed = Util::Vec2(0, 0);

    static_cast<BodyContainer&>(_world).add(*this);
  }

  Body::~Body()
  {
    static_cast<BodyContainer&>(_world).remove(*this);
  }

  void	Body::setSpeed(Util::Vec2& speed)
  {
    _speed = speed;
  }

  Util::Vec2&	Body::getSpeed()
  {
    return (_speed);
  }

  void	Body::setPosition(Util::Vec2& position)
  {
    _position = position;
  }

  Util::Vec2&	Body::getPosition()
  {
    return (_position);
  }

  void	Body::update(float time)
  {
    _position += _speed * time;
    notifyMove();
  }

  void	Body::notifyMove()
  {
    const BodyEvent::Move&	event = BodyEvent::Move(_position);

    notifyObservers(event);
  }
};
