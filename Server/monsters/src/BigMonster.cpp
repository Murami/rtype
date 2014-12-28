#include "BigMonster.hh"
#include "Projectile.hh"
#include "DestroyableSet.hh"

namespace Game
{
  BigMonster::BigMonster(Core& game) : Monster(game, T_MONSTER_BIG)
  {
  }

  BigMonster::~BigMonster()
  {
  }

  void	BigMonster::update(float /*time*/)
  {
  }

  void	BigMonster::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	BigMonster::onCollide(Projectile& projectile)
  {
    if (!projectile.isFriend() || !this->isAlive())
      return ;
    projectile.kill();
    _life -= projectile.getDamage();
  }

  void	BigMonster::onCollide(Monster& /*monster*/)
  {
  }

  void	BigMonster::onCollide(DestroyableSet& set)
  {
    set.kill();
  }
};

extern "C" std::string	get_monster_name()
{
  return ("BigMonster");
}

extern "C" void*	instantiate_plugin(void* ptrgame)
{
  Game::Core*	game = reinterpret_cast<Game::Core*>(ptrgame);

  return (new Game::BigMonster(*game));
}
