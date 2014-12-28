#ifndef DESTROYABLE_SET
#define DESTROYABLE_SET

#include "Entity.hh"

namespace Game
{
  class DestroyableSet : public Entity
  {
  public:
    DestroyableSet(Core& game);
    ~DestroyableSet();

    bool	isAlive();

    void	update(float time);

    void	onCollide(Entity& entity);
    void	onCollide(Player& player);
    void	onCollide(Projectile& projectile);
    void	onCollide(Monster& monster);
    void	onCollide(DestroyableSet& set);
  };
};

#endif /* DESTROYABLE_SET */
