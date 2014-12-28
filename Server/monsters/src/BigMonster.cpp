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
    static bool	init = false;
    static bool	goUp = false;
    static bool	goDown = true;

    if (!init)
      {
	init = true;
	setSpeed(Util::Vec2(50, 50));
      }
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
