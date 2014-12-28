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

    enum EntityType
    {
      T_CAMERA            = 1,
      T_PLAYER_1          = 2,
      T_PLAYER_2          = 3,
      T_PLAYER_3          = 4,
      T_PLAYER_4          = 5,
      T_MONSTER_LITTLE    = 6,
      T_MONSTER_BIG       = 7,
      T_WALL_1            = 10,
      T_WALL_2            = 11,
      T_WALL_3            = 12,
      T_WALL_4            = 13,
      T_BONUS_1           = 14,
      T_BONUS_2           = 15,
      T_BONUS_3           = 16,
      T_BONUS_4           = 17,
      T_MISSILE_FRIENDLY_LITTLE   = 18,
      T_MISSILE_FRIENDLY_BIG      = 19,
      T_MISSILE_ENNEMY_LITTLE     = 20,
      T_MISSILE_ENNEMY_BIG        = 21
    };

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
    EntityType    _type;

  public:
    Entity(Core& game, bool isfriend, EntityType type);
    virtual ~Entity();

    void		setSpeed(const Util::Vec2& speed);
    const Util::Vec2&	getSpeed() const;
    void		setPosition(const Util::Vec2& position);
    const Util::Vec2&	getPosition() const;
    void		setLife(int life);
    int			getLife() const;
    Physic::Body&	getBody();
    void		kill();
    bool		isAlive() const;
    unsigned int	getId() const;
    Core&		getCore();
    void		isToDeleted(bool);
    bool		isToDeleted() const;
    EntityType  getType() const;

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
