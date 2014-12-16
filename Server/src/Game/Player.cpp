#include "Game/Player.hh"

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

  Player::Player(Core& game) :
    Entity(game)
  {
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

    for (it = _inputs.begin(); it != _inputs.end(); it++)
      (this->*_actions[*it])();

    // TODO Normalize speed (if not == 0 !)
  }

  void	Player::onCollide(Entity& entity)
  {
    entity.onCollide(*this);
  }

  void	Player::onCollide(Player& /*player*/)
  {
    // TODO Players can't pass through their mates
  }

  void	Player::onCollide(Projectile& /*projectile*/)
  {
    // TODO Missile die and player loose some life
  }

  void	Player::onCollide(Monster& /*monster*/)
  {
    // TODO Player and monster loose life
    // Do they pass through each other ?
  }

  void	Player::onCollide(DestroyableSet& /*set*/)
  {
    // TODO Player loose some life ans then set die

  }

  void	Player::onForward()
  {
  }

  void	Player::onBackward()
  {
  }

  void	Player::onLeft()
  {
  }

  void	Player::onRight()
  {
  }

  void	Player::onPrimaryFire()
  {
  }

  void	Player::onSecondaryFire()
  {
  }
};
