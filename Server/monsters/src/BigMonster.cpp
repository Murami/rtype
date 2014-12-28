#include "BigMonster.hh"

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

  void	BigMonster::onCollide(Entity& /*entity*/)
  {
  }

  void	BigMonster::onCollide(Projectile& /*projectile*/)
  {
  }

  void	BigMonster::onCollide(Monster& /*monster*/)
  {
  }

  void	BigMonster::onCollide(Player& /*monster*/)
  {
  }


  void	BigMonster::onCollide(DestroyableSet& /*set*/)
  {
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
