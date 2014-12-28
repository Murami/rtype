#include "LittleMonster.hh"

namespace Game
{
  LittleMonster::LittleMonster(Core& game) : Monster(game, T_MONSTER_BIG)
  {
  }

  LittleMonster::~LittleMonster()
  {
  }

  void	LittleMonster::update(float /*time*/)
  {
  }

  void	LittleMonster::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	LittleMonster::onCollide(Projectile& projectile)
  {
    if (!projectile.isFriend() || !this->isAlive())
      return;
    projectile.kill();
    _life -= projectile.getDamage();
  }

  void	LittleMonster::onCollide(Monster& /*monster*/)
  {
  }

  void	LittleMonster::onCollide(DestroyableSet& set)
  {
    set.kill();
  }
};

extern "C" std::string	get_monster_name()
{
  return ("LittleMonster");
}

extern "C" void*	instantiate_plugin(void* ptrgame)
{
  Game::Core*	game = reinterpret_cast<Game::Core*>(ptrgame);

  return (new Game::LittleMonster(*game));
}
