#include "Game/Monster.hh"

namespace Game
{
  Monster::Monster(Core& game) :
    Entity(game, false, T_MONSTER_LITTLE)
  {
  }

  Monster::~Monster()
  {
  }

  void	Monster::update(float /*time*/)
  {
  }

  void	Monster::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	Monster::onCollide(Player& /*player*/)
  {
  }

  void	Monster::onCollide(Projectile& /*projectile*/)
  {
  }

  void	Monster::onCollide(Monster& /*monster*/)
  {
  }

  void	Monster::onCollide(DestroyableSet& /*set*/)
  {
  }
};
