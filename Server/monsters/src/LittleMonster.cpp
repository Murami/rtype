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

  void	LittleMonster::onCollide(Entity& /*entity*/)
  {
  }

  void	LittleMonster::onCollide(Projectile& /*projectile*/)
  {
  }

  void	LittleMonster::onCollide(Monster& /*monster*/)
  {
  }

  void	LittleMonster::onCollide(Player& /*player*/)
  {
  }

  void	LittleMonster::onCollide(DestroyableSet& /*set*/)
  {
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
