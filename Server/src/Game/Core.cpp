#include "Game/Core.hh"
#include "Game/Entity.hh"
#include "Game/Player.hh"
#include "Game/CoreEventSpawn.hh"
#include "Game/Projectile.hh"
#include <iostream>

namespace Game
{
  Core::Core() :
    _alive(true),
    _playercount(0)
  {
  }

  Core::~Core()
  {
  }

  void	Core::update(float time)
  {
    std::list<Entity*>::iterator	it;

    _world.update(time);
    for (it = _entities.begin(); it != _entities.end(); it++)
      (*it)->update(time);
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

  void			Core::addMissile(const Player& player)
  {
    Projectile*			projectile = new Projectile(*this, true, 100,
							    player.getPosition());
    const CoreEvent::Spawn&	spawn = CoreEvent::Spawn(*projectile);

    _entities.push_back(projectile);
    notifyObservers(spawn);
  }
};
