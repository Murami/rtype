#ifndef APPLICATION_ROOM
#define APPLICATION_ROOM

#include <list>
#include <chrono>
#include <string>
#include "Util/Thread.hpp"
#include "Util/IDGenerator.hh"
#include "Game/CoreEventReceiver.hh"
#include "Game/EntityEventReceiver.hh"
#include "Game/Core.hh"
#include "Network/TimerObserver.hh"
#include "Network/Timer.hh"

namespace Application
{
  class Server;
  class ClientRoom;
  class ClientServer;

  class Room : public Game::CoreEventReceiver,
	       public Game::EntityEventReceiver,
	       public Network::TimerObserver
  {
    typedef std::chrono::duration<int, std::milli> duration_milli;

  private:
    static Util::IDGenerator			_generator;
    unsigned int				_id;
    Server&					_server;
    std::list<ClientRoom*>			_clients;
    Game::Core					_game;
    std::chrono::system_clock::duration		_time;
    std::string					_name;
    std::string					_pass;
    Network::Timer				_timer;
    bool					_gamestarted;

  public:
    Room(Server& server, const std::string& name, const std::string& pass);
    ~Room();

    void				startGame();
    void				stopGame();
    bool				isGameStarted() const;
    bool				isReady() const;

    void				onTimeout(Network::Timer& timer);
    void				receive(const Game::Entity& entity, const Game::EntityEvent::Move& event);
    void				receive(const Game::Entity& entity, const Game::EntityEvent::Life& event);
    void				receive(const Game::Core& core, const Game::CoreEvent::Spawn& event);
    void				receive(const Game::Core& core, const Game::CoreEvent::Destroy& event);

    ClientRoom*				addClient(ClientServer* clientserver, bool host);
    void				deleteClient(ClientServer* clientserver);

    unsigned int			getID() const;
    const std::string&			getPass() const;
    const std::string&			getName() const;
    const std::list<ClientRoom*>&	getClients() const;
    unsigned int			getNbClient() const;

    bool				testConnection(const std::string& password) const;
    bool				isFull() const;

    Game::Core&				getGame();

    void				close();
  };
};

#endif /* APPLICATION_ROOM */
