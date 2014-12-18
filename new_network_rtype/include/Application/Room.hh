#ifndef APPLICATION_ROOM
#define APPLICATION_ROOM

#include <list>
#include <chrono>
#include "Util/Thread.hpp"
#include "Game/CoreEventReceiver.hh"
#include "Game/EntityEventReceiver.hh"
#include "Game/Core.hh"
#include "Network/TimerObserver.hh"
#include "Network/Timer.hh"

namespace Application
{
  class Server;
  class ClientRoom;

  class Room : public Game::CoreEventReceiver,
	       public Game::EntityEventReceiver,
	       public Network::TimerObserver
  {
    typedef std::chrono::duration<int, std::milli> duration_milli;

  private:
    Server&					_server;
    std::list<ClientRoom*>			_rooms;
    Game::Core					_game;
    std::chrono::system_clock::duration		_time;

  public:
    Room(Server& server);
    ~Room();

    void	onTimeout(Network::Timer& timer);

    void	receive(const Game::Entity& entity, const Game::EntityEvent::Move& event);
    void	receive(const Game::Entity& entity, const Game::EntityEvent::Life& event);
    void	receive(const Game::Core& core, const Game::CoreEvent::Spawn& event);
    void	receive(const Game::Core& core, const Game::CoreEvent::Destroy& event);
  };
};

#endif /* APPLICATION_ROOM */
