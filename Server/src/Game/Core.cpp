#include "Game/Core.hh"
#include "Game/Entity.hh"
#include "Game/Player.hh"

namespace Game
{
  Core::Core() :
    _alive(true)
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
    Player*	player = new Player(*this);

    _entities.push_back(player);
    return (*player);
  }

  Physic::World&	Core::getWorld()
  {
    return (_world);
  }
};
