#include "LittleMonster.hh"
#include "Projectile.hh"
#include "DestroyableSet.hh"

namespace Game
{
  LittleMonster::LittleMonster(Core& game) : Monster(game, T_MONSTER_LITTLE)
  {
    setSpeed(Util::Vec2(-100, 0));
    _body.setSize(Util::Vec2(21 * 3, 24 * 3));
  }

  LittleMonster::~LittleMonster()
  {
  }

  void	LittleMonster::update(float /*time*/)
  {
    Util::Vec2  pos = _body.getPosition();

    if (_body.getPosition().x + (_body.getSize().x / 2) < -_body.getSize().x)
      _core.deleteEntity(this);
    if (_body.getPosition().y - (_body.getSize().y / 2) < 0)
      pos.y = _body.getSize().y / 2;
    else if ((_body.getPosition().y + (_body.getSize().y / 2)) > 1080)
      pos.y = 1080 - _body.getSize().y / 2;
    _body.setPosition(pos);
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
    if (_life <= 0)
      kill();
  }

  void	LittleMonster::onCollide(Monster& /*monster*/)
  {
  }

  void	LittleMonster::onCollide(Player& entity)
  {
    if (entity.getType() == T_PLAYER_1 ||
      entity.getType() == T_PLAYER_2 ||
      entity.getType() == T_PLAYER_3 ||
      entity.getType() == T_PLAYER_4)
    {
      entity.setLife(entity.getLife - 34);
    }
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
