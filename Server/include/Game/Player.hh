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
	Forward = 0,
	Backward = 1,
	Left = 2,
	Right = 3,
	PrimaryFire = 4,
	SecondaryFire = 5,
	InputMax
      };

  private:
    typedef void (Player::*PlayerAction)();

  private:
    std::list<Input>	_inputs;
    static PlayerAction	_actions[InputMax];
    unsigned int	_num;
    float		_timeMissile;
    bool		_canFireMissile;

  public:
    Player(Core& game, int num);
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

    unsigned int	getNum() const;
  };
};

#endif /* GAME_PLAYER */
