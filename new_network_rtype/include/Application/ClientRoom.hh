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
    bool		_host;

  public:
    ClientRoom(Room& room, ClientServer& clientserver, bool host);
    ~ClientRoom();

    const std::string&	getName() const;
    const void		notifyState(unsigned int state) const;
    bool		isHost() const;
    ClientServer&	getClientServer() const;
    Room*		getRoom() const;
  };
};

#endif /* CLIENT_ROOM */
