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

  const void		ClientRoom::notifyState(unsigned int state) const
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
};
