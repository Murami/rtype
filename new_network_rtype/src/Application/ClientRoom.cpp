#include "Application/ClientRoom.hh"

namespace Application
{
  ClientRoom::ClientRoom(Room& room, ClientServer& clientserver) :
    _room(room),
    _clientserver(clientserver)
  {
  }

  ClientRoom::~ClientRoom()
  {
  }
};
