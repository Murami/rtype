
#include "GameController.hh"
#include "GameView.hh"
#include "Player.hh"
#include "Monster.hh"
#include "BigRocket.hh"
#include "LittleRocket.hh"

GameController::GameController(GameView& view)
  : _view(view)
{
  (void)_view;
}

GameController::~GameController()
{

}

void	GameController::spawnEntity(int id, RtypeProtocol::Entity entity)
{
  IObject *obj = NULL;

  switch (entity)
    {
    case RtypeProtocol::T_PLAYER_1:
      obj = new Player(1);
      break;
    case RtypeProtocol::T_PLAYER_2:
      obj = new Player(2);
      break;
    case RtypeProtocol::T_PLAYER_3:
      obj = new Player(3);
      break;
    case RtypeProtocol::T_PLAYER_4:
      obj = new Player(4);
      break;
    case RtypeProtocol::T_MONSTER_LITTLE:
      obj = new Monster(2);
      break;
    case RtypeProtocol::T_MONSTER_BIG:
      obj = new Monster(1);
      break;
    case RtypeProtocol::T_MISSILE_FRIENDLY_LITTLE:
      obj = new LittleRocket();
      break;
    case RtypeProtocol::T_MISSILE_FRIENDLY_BIG:
      obj = new BigRocket();
      break;
    case RtypeProtocol::T_MISSILE_ENNEMY_LITTLE:
      obj = new LittleRocket(false);
      break;
    case RtypeProtocol::T_MISSILE_ENNEMY_BIG:
      obj = new BigRocket(false);
      break;
    default:						//Ajouter la creation des Wall / Bonus / Camera
      break;
    }
  _view.add(id, obj);
}

void	GameController::updateEntityPosition(int id, RtypeProtocol::Position pos)
{
  _view.updateById(id, pos);
}

void	GameController::update()
{
  
}

void	GameController::setGameListener(IGameListener* listener)
{
  _listener = listener;
}
