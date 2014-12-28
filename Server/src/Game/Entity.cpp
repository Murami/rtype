#include "Game/Entity.hh"
#include "Game/Core.hh"
#include "Game/EntityEventMove.hh"
#include "Game/CollisionEvent.hh"
#include "Physic/BodyEventCollide.hh"
#include "Game/EntityEventDeath.hh"
#include "Game/EntityEventLife.hh"

namespace Game
{
  Util::IDGenerator	Entity::_generator = Util::IDGenerator();

  Entity::Entity(Core& game, bool isfriend, EntityType type) :
    _core(game),
    _body(game.getWorld(), isfriend),
    _life(100),
    _maxlife(100),
    _alive(true)
  {
    _type = type;
    _id = _generator.generate();
    _toDeleted = false;
    _body.addObserver(*this);
  }

  Entity::~Entity()
  {
    // TODO delete observer ????
  }

  void	Entity::setSpeed(const Util::Vec2& speed)
  {
    const EntityEvent::Move& 	move = EntityEvent::Move(_body.getPosition());

    _body.setSpeed(speed);
    notifyObservers(move);
  }

  const Util::Vec2&	Entity::getSpeed() const
  {
    return (_body.getSpeed());
  }

  void		Entity::setPosition(const Util::Vec2& position)
  {
    _body.setPosition(position);
  }

  const Util::Vec2&	Entity::getPosition() const
  {
    return (_body.getPosition());
  }

  void		Entity::setLife(int life)
  {
    _life = life;
    if (_life <= 0)
      kill();
    EntityEvent::Life msg(life);

    notifyObservers(msg);
  }

  int		Entity::getLife() const
  {
    return (_life);
  }

  Physic::Body&	Entity::getBody()
  {
    return (_body);
  }

  void		Entity::kill()
  {
    _alive = false;
    EntityEvent::Death death;

    notifyObservers(death);
  }

  bool		Entity::isAlive() const
  {
    return (_alive);
  }

  unsigned int	Entity::getId() const
  {
    return (_id);
  }

  Core&		Entity::getCore()
  {
    return (_core);
  }

  void		Entity::isToDeleted(bool toDeleted)
  {
    _toDeleted = toDeleted;
  }

  bool		Entity::isToDeleted() const
  {
    return (_toDeleted);
  }

  void		Entity::receive(const Physic::Body& body,
				const Physic::BodyEvent::Move& /*event*/)
  {
    const EntityEvent::Move& 	move = EntityEvent::Move(body.getPosition());

    notifyObservers(move);
  }

  void		Entity::receive(const Physic::Body& /*body*/,
				const Physic::BodyEvent::Collide& event)
  {
    const CollisionEvent&	collisionevent = CollisionEvent(*this);

    std::cout << " .R1. ";
    event.getBody().notifyObservers(collisionevent);
  }

  void		Entity::receive(const Physic::Body& /*body*/, const CollisionEvent& event)
  {
    std::cout << " .R2. " << std::endl;
    event._entity.onCollide(*this);
  }

  EntityType  Entity::getType() const
  {
    return (_type);
  }
};
