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
    _size = Util::Vec2(0, 0);

    static_cast<BodyContainer&>(_world).add(*this);
  }

  Body::~Body()
  {
    static_cast<BodyContainer&>(_world).remove(*this);
  }

  void			Body::setSpeed(const Util::Vec2& speed)
  {
    std::cout << "set speed IUL EST LAS !!!!!" << std::endl;
    _speed = speed;
  }

  const Util::Vec2&	Body::getSpeed() const
  {
    return (_speed);
  }

  void			Body::setSize(const Util::Vec2& size)
  {
    _size = size;
  }

  const Util::Vec2&	Body::getSize() const
  {
    return (_size);
  }

  void			Body::setPosition(const Util::Vec2& position)
  {
    _position = position;
  }

  const Util::Vec2&	Body::getPosition() const
  {
    return (_position);
  }

  void			Body::update(float time)
  {
    if (_speed.x != 0 || _speed.y != 0)
      {
	_position += _speed * time;
	notifyMove();
      }
  }

  void			Body::notifyMove()
  {
    const BodyEvent::Move&	event = BodyEvent::Move(_position);

    notifyObservers(event);
  }

  bool		Body::collide(const Body& body)
  {
    float	left1	= this->_position.x - _size.x / 2;
    float	right1	= this->_position.x + _size.x / 2;
    float	top1	= this->_position.y + _size.y / 2;
    float	bottom1 = this->_position.y - _size.y / 2;
    float	left2	= body.getPosition().x - body.getSize().x / 2;
    float	right2	= body.getPosition().x + body.getSize().x / 2;
    float	top2	= body.getPosition().y + body.getSize().y / 2;
    float	bottom2 = body.getPosition().y - body.getSize().y / 2;

    // TODO Compute collisions infos
    if (((left1 > left2 && left1 < right2) || (right1 > left2 && right1 < right2)) &&
	((top1 > bottom2 && top1 < top2) || (bottom1 > bottom2 && bottom1 < top2)))
      return (true);
    return (false);
  }
};
