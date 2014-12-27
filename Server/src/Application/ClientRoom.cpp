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
  }

  ClientRoom::~ClientRoom()
  {
  }

  //////////////////////////////
  /// Protocol Notifications ///
  //////////////////////////////

  void		ClientRoom::notify(const RtypeProtocol::State* state)
  {
    notifyState(state->state);
  }

  void		ClientRoom::notify(const RtypeProtocol::EntityRequest*)
  {
    // TODO request entity (BONUS --- )
  }

  ////////////////////////
  /// "Start the game" ///
  ////////////////////////

  void		ClientRoom::addToGame()
  {
    std::cout << "add to game" << std::endl;
    _player = &_room.getGame().addPlayer();
  }

  ///////////////
  /// Getters ///
  ///////////////

  const std::string&	ClientRoom::getName() const
  {
    return (_clientserver.getName());
  }

  ClientServer&		ClientRoom::getClientServer() const
  {
    return (_clientserver);
  }

  Room*			ClientRoom::getRoom() const
  {
    return (&_room);
  }

  bool			ClientRoom::isHost() const
  {
    return (_host);
  }

  ////////////////////////
  /// Privates methods ///
  ////////////////////////

  void	ClientRoom::notifyState(unsigned int state)
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
