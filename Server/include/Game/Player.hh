#ifndef GAME_PLAYER
#define GAME_PLAYER

#include "Entity.hh"

namespace Game
{
  class Player : public Entity
  {
  public:
    enum Input
      {
	Forward,
	Backward,
	Left,
	Right,
	PrimaryFire,
	SecondaryFire,
	InputMax
      };

  private:
    typedef void (Player::*PlayerAction)();

    std::list<Input>				_inputs;
    // static std::map<Input, PlayerAction>	_actions;
    static PlayerAction				_actions[InputMax];

  public:
    Player(Core& game);
    ~Player();

    void	addInput(Input input);
    void	clearInput();
    void	update(float time);

    void	onCollide(Entity& entity);
    void	onCollide(Player& player);
    void	onCollide(Projectile& projectile);
    void	onCollide(Monster& monster);
    void	onCollide(DestroyableSet& set);

    void	onForward();
    void	onBackward();
    void	onLeft();
    void	onRight();
    void	onPrimaryFire();
    void	onSecondaryFire();
  };
};

#endif /* GAME_PLAYER */
