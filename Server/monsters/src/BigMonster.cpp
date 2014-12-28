#include "BigMonster.hh"
#include "Projectile.hh"
#include "DestroyableSet.hh"
#include <iostream>

namespace Game
{
  BigMonster::BigMonster(Core& game) : Monster(game, T_MONSTER_BIG)
  {
    setSpeed(Util::Vec2(-100, 0));
    _body.setSize(Util::Vec2(63 * 3, 48 * 3));
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
    // if (getPosition().x >= 500 || getPosition().y >= 900)
    //   setSpeed(Util::Vec2(0, -100));
    // if (getPosition().y <= 50)
    //   setSpeed(Util::Vec2(0, 100));
    Util::Vec2  pos = _body.getPosition();
    Util::Vec2	size(63 * 3, 48 * 3);

    if (_body.getPosition().x + (_body.getSize().x / 2) < -_body.getSize().x)
      _core.deleteEntity(this);
    if (_body.getPosition().y - (_body.getSize().y / 2) < 0)
      pos.y = _body.getSize().y / 2;
    else if ((_body.getPosition().y + (_body.getSize().y / 2)) > 1080)
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
    std::cout << "life : " << _life << std::endl;
    if (_life <= 0)
      kill();
  }

  void	BigMonster::onCollide(Monster& /*monster*/)
  {
  }

  void	BigMonster::onCollide(Player& entity)
  {
    entity.setLife(entity.getLife() - 67);
    kill();
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
