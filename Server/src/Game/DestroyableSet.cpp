#include "Game/DestroyableSet.hh"


namespace Game
{
  DestroyableSet::DestroyableSet(Core& game) :
    Entity(game)
  {
  }

  DestroyableSet::~DestroyableSet()
  {
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
