#ifndef CLIENT_ROOM
#define CLIENT_ROOM

#include <string>
#include "Game/Player.hh"
#include "Protocol/RtypeProtocol.hh"

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

    // Protocol Notifications
    void		notify(const RtypeProtocol::State* state);
    void		notify(const RtypeProtocol::EntityRequest* request);

    // "Start the game"
    void		addToGame();

    // Getters
    const std::string&	getName() const;
    ClientServer&	getClientServer() const;
    Room*		getRoom() const;
    bool		isHost() const;

  private:
    void		notifyState(unsigned int state);
  };
};

#endif /* CLIENT_ROOM */
