#include "Game/Monster.hh"

namespace Game
{
  Monster::Monster(Core& game) :
    Entity(game, false, T_MONSTER_LITTLE)
  {
  }

  Monster::~Monster()
  {
  }

  void	Monster::update(float /*time*/)
  {
    Util::Vec2  pos = _body.getPosition();

    if (_body.getPosition().x + (_body.getSize().x / 2) < 0)
      _core.deleteEntity(this);
    if (_body.getPosition().y - (_body.getSize().y / 2) < 0)
      pos.y = _body.getSize().y / 2;
    else if ((_body.getPosition().y - (_body.getSize().y / 2)) > (1080 - _body.getSize().y))
      pos.y = 1080 - _body.getQize().y / 2;
    _body.setPosition(pos);
  }

  void	Monster::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	Monster::onCollide(Player& // player
			   )
  {
    //    player.set
  }

  void	Monster::onCollide(Projectile& /*projectile*/)
  {
  }

  void	Monster::onCollide(Monster& /*monster*/)
  {
  }

  void	Monster::onCollide(DestroyableSet& /*set*/)
  {
  }
};
