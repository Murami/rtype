#ifndef GAME_ENTITY
#define GAME_ENTITY

#include "Physic/Body.hh"
#include "Physic/BodyEventReceiver.hh"
#include "Util/Observer.hpp"
#include "Util/Observable.hpp"
#include "Util/IDGenerator.hh"
#include "Util/Vec2.hh"
#include "Game/CollisionReceiver.hh"
#include "Game/Core.hh"

namespace Game
{
  class Player;
  class Projectile;
  class Monster;
  class DestroyableSet;
  class EntityEvent;

  class Entity : public Util::Observable<Entity, EntityEvent>,
		 public CollisionReceiver
  {
  protected:
    static Util::IDGenerator	_generator;
    Core&			_core;
    Physic::Body		_body;
    int				_life;
    int				_maxlife;
    bool			_alive;
    unsigned int		_id;
    bool			_toDeleted;

  public:
    Entity(Core& game);
    virtual ~Entity();

    void		setSpeed(const Util::Vec2& speed);
    const Util::Vec2&	getSpeed() const;
    void		setPosition(const Util::Vec2& position);
    const Util::Vec2&	getPosition() const;
    void		setLife(int life);
    int			getLife() const;
    void		kill();
    bool		isAlive() const;
    unsigned int	getId() const;
    Core&		getCore();
    void		isToDeleted(bool);
    bool		isToDeleted() const;

    virtual void	update(float time) = 0;
    virtual void	onCollide(Entity& entity) = 0;
    virtual void	onCollide(Player& ship) = 0;
    virtual void	onCollide(Projectile& projectile) = 0;
    virtual void	onCollide(Monster& monster) = 0;
    virtual void	onCollide(DestroyableSet& set) = 0;

    void		receive(const Physic::Body& body, const Physic::BodyEvent::Move& event);
    void		receive(const Physic::Body& body, const Physic::BodyEvent::Collide& event);
    void		receive(const Physic::Body& body, const CollisionEvent& event);
  };
};

#endif /* GAME_ENTITY */
