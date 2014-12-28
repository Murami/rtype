#include "Game/Entity.hh"
#include "Game/Core.hh"
#include "Game/EntityEventMove.hh"

namespace Game
{
  Util::IDGenerator	Entity::_generator = Util::IDGenerator();

  Entity::Entity(Core& game) :
    _core(game),
    _body(game.getWorld()),
    _life(100),
    _maxlife(100),
    _alive(true)
  {
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
    _body.setSpeed(speed);
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
  }

  int		Entity::getLife() const
  {
    return (_life);
  }

  void		Entity::kill()
  {
    _alive = false;
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

  void		Entity::receive(const Physic::Body& /*body*/, const Physic::BodyEvent::Collide& /*event*/)
  {
    // TODO notifier l'autre body en envoyant l'entity dans le message
  }

  void		Entity::receive(const Physic::Body& /*body*/, const CollisionEvent& /*event*/)
  {
    // TODO notifer le serveur d'un collision
  }
};
