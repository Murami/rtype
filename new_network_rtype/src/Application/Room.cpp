#include "Application/Room.hh"

namespace Application
{
  Room::Room(Server& server, const std::string& name, const std::string& pass) :
    _server(server)
  {
    _time = std::chrono::system_clock::now().time_since_epoch();
    _name = name;
    _pass = pass;
  }

  Room::~Room()
  {
  }

  void	Room::onTimeout(Network::Timer& timer)
  {
    std::chrono::system_clock::duration	time;
    std::chrono::system_clock::duration	timediff;

    time = std::chrono::system_clock::now().time_since_epoch();
    timediff = time - _time;
    _game.update(static_cast<float>(std::chrono::duration_cast<duration_milli>(timediff).count()) / 1000.f);
    time = std::chrono::system_clock::now().time_since_epoch();
    timediff = time - _time;
    timer.setTimeout(duration_milli(20) - timediff);
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

  bool	Room::testConnection(const std::string& name, const std::string& password)
  {
    return (name == _name && password == _pass);
  }
};
