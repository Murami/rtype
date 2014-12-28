#include "Application/ClientRoom.hh"
#include "Application/Room.hh"
#include "Application/ClientServer.hh"
#include "Application/Server.hh"
#include "Protocol/Protocole.hh"

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

  void		ClientRoom::notify(const RtypeProtocol::EntityRequest* request)
  {
    Game::Entity*	entity = _room.getGame().getEntity(request->id);

    if (entity)
      {
	RtypeProtocol::Header	header;
	RtypeProtocol::Spawn	spawn;
	Network::packet*	packed;
	Network::packet*	hpacked;
	char			buffer[4096];

	header.type = RtypeProtocol::T_SPAWN;
	header.type = sizeof(RtypeProtocol::Spawn);

	spawn.id = entity->getId();
	spawn.type = RtypeProtocol::T_PLAYER_1; // TODO gerer le type de l'entity !!!
	spawn.position.x = entity->getPosition().x;
	spawn.position.y = entity->getPosition().y;
	spawn.life = entity->getLife();

	packed = _clientserver.getServer().getProtocoleUdp().pack(&spawn);
	hpacked = _clientserver.getServer().getProtocoleUdp().pack(&header);

	std::memcpy(buffer, hpacked->getData(), hpacked->getSize());
	std::memcpy(buffer + hpacked->getSize(), packed->getData(), packed->getSize());

	_clientserver.sendUdp(buffer, hpacked->getSize() + packed->getSize());

	delete (hpacked);
	delete (packed);
      }
    else
      {
	RtypeProtocol::Header		header;
	RtypeProtocol::Destruction	destruction;
	Network::packet*		packed;
	Network::packet*		hpacked;
	char				buffer[4096];

	header.type = RtypeProtocol::T_DESTRUCTION;
	header.type = sizeof(RtypeProtocol::Destruction);

	destruction.id = request->id;

	packed = _clientserver.getServer().getProtocoleUdp().pack(&destruction);
	hpacked = _clientserver.getServer().getProtocoleUdp().pack(&header);

	std::memcpy(buffer, hpacked->getData(), hpacked->getSize());
	std::memcpy(buffer + hpacked->getSize(), packed->getData(), packed->getSize());

	_clientserver.sendUdp(buffer, hpacked->getSize() + packed->getSize());

	delete (hpacked);
	delete (packed);
      }
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

  Room*			ClientRoom::getRoom()
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
