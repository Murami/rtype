#include "Application/ClientRoom.hh"
#include "Application/Room.hh"
#include "Application/ClientServer.hh"

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

  const std::string&	ClientRoom::getName() const
  {
    return (_clientserver.getName());
  };
};
