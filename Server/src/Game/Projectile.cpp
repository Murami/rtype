#include "Game/Projectile.hh"
#include "Game/Monster.hh"
#include "Game/DestroyableSet.hh"

namespace Game
{
  Projectile::Projectile(Core& game, bool isFriend, int damage,
			 const Util::Vec2& position) :
    Entity(game, isFriend, T_MISSILE),
    _isFriend(isFriend),
    _damage(damage)
  {
    Util::Vec2	pos(16, 8);

    _body.setSize(pos);
    setPosition(position);
    setSpeed(Util::Vec2(1500, 0));
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
    
    Util::Vec2	pos = _body.getPosition();

    if (_body.getPosition().x - (_body.getSize().x / 2) < 0)
      _core.deleteEntity(this);
    else if ((_body.getPosition().x - (_body.getSize().x / 2)) > (1920 - _body.getSize().x))
      _core.deleteEntity(this);
    if (_body.getPosition().y - (_body.getSize().y / 2) < 0)
      _core.deleteEntity(this);
    else if ((_body.getPosition().y - (_body.getSize().y / 2)) > (1080 - _body.getSize().y))
      _core.deleteEntity(this);
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
