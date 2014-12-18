#include "Application/Room.hh"
#include "Util/Time.hh"

namespace Application
{
  Room::Room(Server& server) :
    _server(server)
  {
  }

  Room::~Room()
  {
  }

  int	Room::run()
  {
    unsigned int	time;
    unsigned int	newTime;

    time = Util::getCurrentTime();
    while (_game.alive())
      {
	_game.update(static_cast<float>(time) / 1000.f);

	newTime = Util::getCurrentTime();
	if (newTime - time < updatePeriod)
	  Util::sleep(time);
	time = newTime;
      }
    return (0);
  }

  void	Room::receive(const Game::Entity& /*entity*/, const Game::EntityEvent::Move& /*event*/)
  {
  }

  void	Room::receive(const Game::Entity& /*entity*/, const Game::EntityEvent::Life& /*event*/)
  {
  }

  void	Room::receive(const Game::Core& /*core*/, const Game::CoreEvent::Spawn& /*event*/)
  {
  }

  void	Room::receive(const Game::Core& /*core*/, const Game::CoreEvent::Destroy& /*event*/)
  {
  }
};
