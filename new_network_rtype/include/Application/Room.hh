#ifndef APPLICATION_ROOM
#define APPLICATION_ROOM

#include <list>
#include "Util/Thread.hpp"
#include "Game/CoreEventReceiver.hh"
#include "Game/EntityEventReceiver.hh"
#include "Game/Core.hh"

namespace Application
{
  class Server;
  class ClientRoom;

  class Room : public Util::Thread<void>,
	       public Game::CoreEventReceiver,
	       public Game::EntityEventReceiver
  {
    static const unsigned int	updatePeriod = 20;

  private:
    Server&			_server;
    std::list<ClientRoom*>	_rooms;
    Game::Core			_game;

  public:
    Room(Server& server);
    ~Room();

    int	run();

    void	receive(const Game::Entity& entity, const Game::EntityEvent::Move& event);
    void	receive(const Game::Entity& entity, const Game::EntityEvent::Life& event);
    void	receive(const Game::Core& core, const Game::CoreEvent::Spawn& event);
    void	receive(const Game::Core& core, const Game::CoreEvent::Destroy& event);
  };
};

#endif /* APPLICATION_ROOM */
