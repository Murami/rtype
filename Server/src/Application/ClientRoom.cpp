#include "Application/ClientRoom.hh"
#include "Application/Room.hh"
#include "Application/ClientServer.hh"

namespace Application
{
  ClientRoom::ClientRoom(Room& room, ClientServer& clientserver, bool host) :
    _room(room),
    _clientserver(clientserver),
    _host(host)
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

  void		ClientRoom::notify(const RtypeProtocol::State* state)
  {
    notifyState(state->state);
  }

  void		ClientRoom::notify(const RtypeProtocol::EntityRequest*)
  {
    // TODO request entity (BONUS --- )
  }

  void		ClientRoom::notifyState(unsigned int state)
  {
    // DANS L'IDEAL UNE MAP
    _player->clearInput();
    if (state & INPUT_FORWARD)
      _player->addInput(Game::Player::Forward);
    if (state & INPUT_BACKWARD)
      _player->addInput(Game::Player::Backward);
    if (state & INPUT_LEFT)
      _player->addInput(Game::Player::Left);
    if (state & INPUT_RIGHT)
      _player->addInput(Game::Player::Right);
    if (state & INPUT_PRIMARYFIRE)
      _player->addInput(Game::Player::PrimaryFire);
    if (state & INPUT_SECONDARYFIRE)
      _player->addInput(Game::Player::SecondaryFire);
  }

  bool			ClientRoom::isHost() const
  {
    return (_host);
  }

  ClientServer&		ClientRoom::getClientServer() const
  {
    return (_clientserver);
  }

  Room*			ClientRoom::getRoom() const
  {
    return (&_room);
  }
};
