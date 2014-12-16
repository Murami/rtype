#ifndef GAME_MONSTER
#define GAME_MONSTER

#include "Game/Entity.hh"

namespace Game
{
  class Monster : public Entity
  {
  public:
    Monster(Core& game);
    ~Monster();

    void	update(float time);

    void	onCollide(Entity& entity);
    void	onCollide(Player& player);
    void	onCollide(Projectile& projectile);
    void	onCollide(Monster& monster);
    void	onCollide(DestroyableSet& set);
  };
};

#endif /* GAME_MONSTER */
