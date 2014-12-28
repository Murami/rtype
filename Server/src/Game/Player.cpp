#include "Game/Player.hh"
#include "Game/Projectile.hh"
#include "Game/Monster.hh"

namespace Game
{
  Player::PlayerAction	Player::_actions[] =
    {
      &Player::onForward,
      &Player::onBackward,
      &Player::onLeft,
      &Player::onRight,
      &Player::onPrimaryFire,
      &Player::onSecondaryFire
    };

  Player::Player(Core& game, int num) :
    Entity(game), _num(num)
  {
    Util::Vec2	pos(64, 28);

    _body.setSize(pos);
    // TODO a enlever
    // setSpeed(Util::Vec2(10, 0));
  }

  Player::~Player()
  {
  }

  void	Player::addInput(Input input)
  {
    _inputs.push_back(input);
  }

  void	Player::clearInput()
  {
    _inputs.clear();
  }

  void	Player::update(float /*time*/)
  {
    // Input/State Component
    std::list<Input>::iterator	it;

    setSpeed(Util::Vec2(0, 0));
    for (it = _inputs.begin(); it != _inputs.end(); it++)
      (this->*_actions[*it])();

    Util::Vec2	speed;

    speed = getSpeed();

    if (speed.x != 0 || speed.y != 0)
      {
	speed.normalize();
	setSpeed(speed);
      }

    Util::Vec2	pos = _body.getPosition();

    if (_body.getPosition().x - (_body.getSize().x / 2) < 0)
      pos.x = _body.getSize().x / 2;
    else if ((_body.getPosition().x - (_body.getSize().x / 2)) > (1920 - _body.getSize().x))
      pos.x = 1920 - _body.getSize().x / 2;
    if (_body.getPosition().y - (_body.getSize().y / 2) < 0)
      _core.deleteEntity(this);
      // pos.y = _body.getSize().y / 2;
    else if ((_body.getPosition().y - (_body.getSize().y / 2)) > (1080 - _body.getSize().y))
      pos.y = 1080 - _body.getSize().y / 2;
    _body.setPosition(pos);
  }

  void	Player::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	Player::onCollide(Player& /*player*/)
  {
    // TODO Les joueurs se collisionent sans degats
  }

  void	Player::onCollide(Projectile& projectile)
  {
    if (!this->isAlive() || !projectile.isAlive())
      return;

    if (!projectile.isFriend())
      _life -= projectile.getDamage();
    projectile.kill();
  }

  void	Player::onCollide(Monster& monster)
  {
    monster.onCollide(*this);
  }

  void	Player::onCollide(DestroyableSet& /*set*/)
  {
    // TODO Player loose some life ans then set die

  }

  // TODO input methods
  void	Player::onForward()
  {
    setSpeed(getSpeed() + Util::Vec2(0, -1));
  }

  void	Player::onBackward()
  {
    setSpeed(getSpeed() + Util::Vec2(0, 1));
  }

  void	Player::onLeft()
  {
    setSpeed(getSpeed() + Util::Vec2(-1, 0));
  }

  void	Player::onRight()
  {
    setSpeed(getSpeed() + Util::Vec2(1, 0));
  }

  void	Player::onPrimaryFire()
  {
    // TODO primary fire
  }

  void	Player::onSecondaryFire()
  {
    // TODO secondary fire
  }

  unsigned int	Player::getNum() const
  {
    return (_num);
  }
};
