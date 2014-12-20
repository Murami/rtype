#ifndef CLIENT_ROOM
#define CLIENT_ROOM

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
  };
};

#endif /* CLIENT_ROOM */
