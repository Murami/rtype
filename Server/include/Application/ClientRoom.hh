#ifndef CLIENT_ROOM
#define CLIENT_ROOM

namespace Application
{
  class Room;
  class ClientServer;

  class ClientRoom
  {
  private:
    Room&		_room;
    ClientServer&	_clientserver;

  public:
    ClientRoom(Room& room, ClientServer& clientserver);
    ~ClientRoom();
  };
};

#endif /* CLIENT_ROOM */
