
#include <iostream>
#include "GameController.hh"
#include "GameView.hh"
#include "Player.hh"
#include "Monster.hh"
#include "BigRocket.hh"
#include "LittleRocket.hh"
#include <iostream>

GameController::GameController(GameView& view)
  : _view(view)
{
}

GameController::~GameController()
{
  
}

void	GameController::spawnEntity(RtypeProtocol::Spawn spawn)
{
  std::cout << "SPAWNENTITY" << std::endl;
  _spawnList.push_back(spawn);
}

void	GameController::updateSpawnList()
{
  std::list<RtypeProtocol::Spawn>::iterator	it;

  for (it = _spawnList.begin(); it != _spawnList.end(); it++)
    {
      createEntity(it->id, static_cast<RtypeProtocol::Entity>(it->type));
      updateEntityPosition(it->id, it->position);
    }
  _spawnList.clear();
}

void	GameController::updateDestroyList()
{
  std::list<int>::iterator	it;

  for (it = _destroyList.begin(); it != _destroyList.end(); it++)
    {
      _view.erase(*it);
    }
  _destroyList.clear();
}

void GameController::onExit()
{
  _listener->onExitFromGame();
  std::cout << "exit game !!" << std::endl;
}

void	GameController::createEntity(int id, RtypeProtocol::Entity entity)
{
  IObject *obj = NULL;

  std::cout << "ENTITY : " << (int)entity << std::endl;
  switch (entity)
    {
    case RtypeProtocol::T_PLAYER_1:
    std::cout << "new player 1" << std::endl;
      obj = new Player(1);
      break;
    case RtypeProtocol::T_PLAYER_2:
    std::cout << "new player 2" << std::endl;
      obj = new Player(2);
      break;
    case RtypeProtocol::T_PLAYER_3:
    std::cout << "new player 3" << std::endl;
      obj = new Player(3);
      break;
    case RtypeProtocol::T_PLAYER_4:
    std::cout << "new player 4" << std::endl;
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

void	GameController::deleteEntity(int id)
{
  _destroyList.push_back(id);
}

void	GameController::updateEntityPosition(int id, RtypeProtocol::Position pos)
{
  if (_view.updateById(id, pos) == false)
    _listener->onEntityRequestFromGame(id);
}

void	GameController::update(size_t mask)
{
  _listener->onKeyEvent(static_cast<RtypeEvent::eKeyEvent>(mask));
}

void	GameController::setGameListener(IGameListener* listener)
{
  _listener = listener;
}
