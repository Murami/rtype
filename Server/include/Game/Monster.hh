#ifndef GAME_MONSTER
#define GAME_MONSTER

#include "Game/Entity.hh"
#include "Util/APlugin.hh"

namespace Game
{
  class Monster : public Entity,
		  public APlugin
  {
  public:
    Monster(Core& game, EntityType type) : Entity(game, false, type) {}
    virtual ~Monster() {};

    virtual void	update(float time) = 0;

    virtual void	onCollide(Entity& entity) = 0;
    virtual void	onCollide(Player& player) = 0;
    virtual void	onCollide(Projectile& projectile) = 0;
    virtual void	onCollide(Monster& monster) = 0;
    virtual void	onCollide(DestroyableSet& set) = 0;
  };
};

#endif /* GAME_MONSTER */
