#include "Game/DestroyableSet.hh"


namespace Game
{
  DestroyableSet::DestroyableSet(Core& game) :
    Entity(game, false, T_WALL_1)
  {
  }

  DestroyableSet::~DestroyableSet()
  {
  }

  bool	DestroyableSet::isAlive()
  {
    return (_alive);
  }

  void	DestroyableSet::update(float /*time*/)
  {
  }

  void	DestroyableSet::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	DestroyableSet::onCollide(Player& /*player*/)
  {
  }

  void	DestroyableSet::onCollide(Projectile& /*projectile*/)
  {
  }

  void	DestroyableSet::onCollide(Monster& /*monster*/)
  {
  }

  void	DestroyableSet::onCollide(DestroyableSet& /*set*/)
  {
  }
};
