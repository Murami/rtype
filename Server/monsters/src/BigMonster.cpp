#include "BigMonster.hh"
#include "Projectile.hh"
#include "DestroyableSet.hh"

namespace Game
{
  BigMonster::BigMonster(Core& game) : Monster(game, T_MONSTER_BIG)
  {
    setSpeed(Util::Vec2(-100, 0));
  }

  BigMonster::~BigMonster()
  {
  }

  void	BigMonster::update(float /*time*/)
  {
    // static bool	init = false;

    // if (!init)
    //   {
    // 	init = true;
    // 	setSpeed(Util::Vec2(-100, 0));
    //   }
    // if (getPosition().x >= 500)
    //   setSpeed(Util::Vec2(0, -100));
    // if (getPosition().y >= 900)
    //   setSpeed(Util::Vec2(0, -100));
    // else if (getPosition().y <= 50)
    //   setSpeed(Util::Vec2(0, 100));
    // std::cout << "Monster Speed : " << getPosition().x << " " << getPosition().y << std::endl;

    // if (!init)
    //   {
    // 	init = true;
    // 	setSpeed(Util::Vec2(-100, 0));
    //   }
    // if (getPosition().x >= 500 || getPosition().y >= 900)
    //   setSpeed(Util::Vec2(0, -100));
    // if (getPosition().y <= 50)
    //   setSpeed(Util::Vec2(0, 100));
    Util::Vec2  pos = _body.getPosition();

    if (_body.getPosition().x + (_body.getSize().x / 2) < 0)
      _core.deleteEntity(this);
    if (_body.getPosition().y - (_body.getSize().y / 2) < 0)
      pos.y = _body.getSize().y / 2;
    else if ((_body.getPosition().y - (_body.getSize().y / 2)) > (1080 - _body.getSize().y))
      pos.y = 1080 - _body.getSize().y / 2;
    _body.setPosition(pos);
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

  void	BigMonster::onCollide(Player& /*monster*/)
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
