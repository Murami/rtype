#ifndef GAME_ENTITY
#define GAME_ENTITY

#include "Physic/Body.hh"
#include "Physic/BodyEventReceiver.hh"
#include "Util/Observer.hpp"

namespace Game
{
  class Ship;
  class Projectile;
  class Monster;
  class EntityEvent;

  class Entity : public Observable<Entity, Entity>,
		 public Physic::BodyEventReceiver
  {
  protected:
    Physic::Body	_body;
    int			_life;
    bool		_alive;
    unsigned int	_id;

  public:
    Entity();
    virtual ~Entity();

    void		setSpeed(const vec3& speed);
    const vec2&		getSpeed() const;
    void		setPosition(const vec3& position);
    const vec2&		getPosition();
    void		setLife(int life);
    int			getLife();
    void		kill();
    bool		isAlive();
    unsigned int	getId() const;

    virtual void	update(float time) = 0;
    virtual void	onCollide(Entity* entity) = 0;
    virtual void	onCollide(Ship* ship);
    virtual void	onCollide(Projectile* projectile);
    virtual void	onCollide(Monster* monster);

    void		update(Body& body, BodyEvent& event);

    void		receive(Body& body, BodyPositionEvent& event);
    void		receive(Body& body, BodyCollsiionEvent& event);
  };
};

#endif /* GAME_ENTITY */
