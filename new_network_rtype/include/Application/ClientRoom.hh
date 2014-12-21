#ifndef CLIENT_ROOM
#define CLIENT_ROOM

#include <string>
#include "Game/Player.hh"

namespace Application
{
  class Room;
  class ClientServer;

  class ClientRoom
  {
  private:
    Room&		_room;
    ClientServer&	_clientserver;
    Game::Player*	_player;

  public:
    ClientRoom(Room& room, ClientServer& clientserver);
    ~ClientRoom();

    const std::string&	getName() const;
    const void		notifyState(unsigned int state) const;
  };
};

#endif /* CLIENT_ROOM */
