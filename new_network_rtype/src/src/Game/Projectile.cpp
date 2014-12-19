#include "Game/Projectile.hh"
#include "Game/Monster.hh"
#include "Game/DestroyableSet.hh"

namespace Game
{
  Projectile::Projectile(Core& game, bool isFriend, int damage) :
    Entity(game),
    _isFriend(isFriend),
    _damage(damage)
  {
  }

  Projectile::~Projectile()
  {
  }

  bool	Projectile::isFriend() const
  {
    return (_isFriend);
  }

  void	Projectile::update(float /*time*/)
  {
  }

  void	Projectile::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	Projectile::onCollide(Projectile& /*player*/)
  {
    // DO NOTHING
  }

  void	Projectile::onCollide(Player& /*projectile*/)
  {
    // DO NOTING
  }

  void	Projectile::onCollide(Monster& monster)
  {
    monster.onCollide(*this);
  }

  void	Projectile::onCollide(DestroyableSet& set)
  {
    // TODO Notify a death
    set.kill();
  }

  int	Projectile::getDamage()
  {
    return (_damage);
  }
};
