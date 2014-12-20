#include "Application/ClientRoom.hh"
#include "Application/Room.hh"

namespace Application
{
  ClientRoom::ClientRoom(Room& room, ClientServer& clientserver) :
    _room(room),
    _clientserver(clientserver)
  {
    _player = &room.getGame().addPlayer();
  }

  ClientRoom::~ClientRoom()
  {
  }
};
