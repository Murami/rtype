#include "Ship.hh"

namespace Game
{
  Ship::Ship();
  ~Ship::Ship();

  void	Ship::update()
  {
  }

  void	Ship::onCollide(Entity& entity)
  {
  }

  void	Ship::onCollide(Ship& ship)
  {
  }

  void	Ship::onCollide(Projectile& projectile)
  {
  }

  void	Ship::onCollide(Monster& monster)
  {
  }
};
