#ifndef GAME_PROJECTILE
#define GAME_PROJECTILE

#include "Entity.hh"

namespace Game
{
  class Projectile : public Entity
  {
  private:
    bool	_isFriend;
    int		_damage;

  public:
    Projectile(Core& game, bool isFriend,
	       int damage, const Util::Vec2& position);
    ~Projectile();

    bool	isFriend() const;

    void	update(float time);

    void	onCollide(Entity& entity);
    void	onCollide(Player& player);
    void	onCollide(Projectile& projectile);
    void	onCollide(Monster& monster);
    void	onCollide(DestroyableSet& set);

    int		getDamage();
  };
};

#endif /* GAME_PROJECTILE */
