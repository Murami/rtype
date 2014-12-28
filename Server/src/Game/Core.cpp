#include "Game/Core.hh"
#include "Game/Entity.hh"
#include "Game/Player.hh"
#include "Game/CoreEventSpawn.hh"
#include "Game/Projectile.hh"
#include "Game/CoreEventDestroy.hh"
#include "Game/Monster.hh"
#include <iostream>

namespace Game
{
  Core::Core() :
    _alive(true),
    _playercount(0),
    _loader("./monsters")
  {
    _timeSpawn = 0;
    _progress = 0;
  }

  Core::~Core()
  {
  }

  void	Core::update(float time)
  {
    std::list<Entity*>::iterator	it;

    _timeSpawn += time;
    if (_timeSpawn > 2.5)
      {
	_timeSpawn = 0;
	spawnMonster();
      }
    if (_progress > 200)
      {
	_alive = false;
      }
    _world.update(time);
    for (it = _entities.begin(); it != _entities.end(); it++)
      (*it)->update(time);

    // std::list<std::list<Entity*>::iterator> toDelete;
    for (it = _entities.begin(); it != _entities.end(); it++)
      {
	if (!(*it)->isAlive())
	  {
	    (*it)->isToDeleted(true);
	    // toDelete.push_front(it);
	  }
      }
    // std::list<std::list<Entity*>::iterator>::iterator toDeleteIt;
    // for (toDeleteIt = toDelete.begin(); toDeleteIt != toDelete.end(); toDeleteIt++)
    // {
    //   it = (*toDeleteIt);
    //   const CoreEvent::Destroy& destroy = CoreEvent::Destroy(*(*it));

    //   notifyObservers(destroy);
    //   delete (*it);
    //   _entities.erase(it);
    // }

    for (it = _entities.begin(); it != _entities.end(); it++)
      {
	if ((*it)->isToDeleted() == true)
	  {
	    const CoreEvent::Destroy& destroy = CoreEvent::Destroy(*(*it));

	    notifyObservers(destroy);
      if ((*it)->getType() != T_PLAYER_1 &&
        (*it)->getType() != T_PLAYER_2 &&
        (*it)->getType() != T_PLAYER_3 &&
        (*it)->getType() != T_PLAYER_4)
	    delete (*it);
	    it = _entities.erase(it);
	  }
      }
  }

  bool	Core::alive() const
  {
    return (_alive);
  }

  Player&	Core::addPlayer()
  {
    Player*			player = new Player(*this, _playercount);
    const CoreEvent::Spawn&	spawn = CoreEvent::Spawn(*player);

    std::cout << "Add new player" << std::endl;
    _entities.push_back(player);
    player->setPosition(Util::Vec2(30, 20 + _playercount * 20));
    _playercount++;
    notifyObservers(spawn);
    return (*player);
  }

  Physic::World&	Core::getWorld()
  {
    return (_world);
  }

  Entity*		Core::getEntity(unsigned int id)
  {
    std::list<Entity*>::iterator	it;

    for (it = _entities.begin(); it != _entities.end(); it++)
      {
	if ((*it)->getId() == id)
	  return (*it);
      }
    return (NULL);
  }

  void	Core::deleteEntity(Entity* entity)
  {
    entity->isToDeleted(true);
  }

  void			Core::addMissile(const Player& player)
  {
    Projectile*			projectile = new Projectile(*this, true, 100,
							    player.getPosition());
    const CoreEvent::Spawn&	spawn = CoreEvent::Spawn(*projectile);

    _entities.push_back(projectile);
    notifyObservers(spawn);
  }

  void			Core::spawnMonster()
  {
    std::list<std::string>::iterator	it;
    std::list<std::string>&		plugins = _loader.getPluginList();
    Monster*				monster;

    _progress++;

    if (plugins.size() == 0)
      return;

    int					rand = std::rand() % plugins.size();

    it = std::next(plugins.begin(), rand);
    monster = _loader.load(*it, this);

    const CoreEvent::Spawn&		spawn = CoreEvent::Spawn(*monster);

    int	y = std::rand() % 1080;
    monster->setPosition(Util::Vec2(2000, y));

    _entities.push_back(monster);
    notifyObservers(spawn);
  }
};
