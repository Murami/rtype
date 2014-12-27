#include "Application/Room.hh"
#include "Application/ClientServer.hh"
#include "Application/ClientRoom.hh"
#include "Application/Server.hh"
#include "Game/CoreEventSpawn.hh"
#include "Game/CoreEventDestroy.hh"
#include "Game/EntityEventMove.hh"
#include "Game/EntityEventLife.hh"

// NEED -> death , hit, bonus

// TODO observe the player !!!!!!

namespace Application
{
  Room::Room(Server& server, const std::string& name, const std::string& pass) :
    _server(server)
  {
    _time = std::chrono::system_clock::now().time_since_epoch();
    _name = name;
    _pass = pass;
    _id = _generator.generate();
    _gamestarted = false;
    std::cout << "add observer to core" << std::endl;
    _game.addObserver(*this);
  }

  Room::~Room()
  {
  }

  void	Room::onTimeout(Network::Timer& timer)
  {
    std::chrono::system_clock::duration	time;
    std::chrono::system_clock::duration	timediff;

    time = std::chrono::system_clock::now().time_since_epoch();
    timediff = time - _time;
    _game.update(static_cast<float>(std::chrono::duration_cast<duration_milli>(timediff).count()) / 1000.f);
    time = std::chrono::system_clock::now().time_since_epoch();
    timediff = time - _time;
    timer.setTimeout(duration_milli(20) - timediff);
  }

  void	Room::receive(const Game::Entity& /*entity*/,
		      const Game::EntityEvent::Move& /*event*/)
  {
  }

  void	Room::receive(const Game::Entity& /*entity*/,
		      const Game::EntityEvent::Life& /*event*/)
  {
  }

  void	Room::receive(const Game::Core& /*core*/,
		      const Game::CoreEvent::Spawn& event)
  {
    RtypeProtocol::Spawn	spawn;
    Network::packet*		packed;

    event.entity.addObserver(*this);
    spawn.id = event.entity.getId();
    spawn.type = RtypeProtocol::T_PLAYER_1;// TODO gerer les player de 1 a 4 dans le gameplay
    spawn.position.x = event.entity.getPosition().x;
    spawn.position.y = event.entity.getPosition().y;
    spawn.life = event.entity.getLife();
    packed = _server.getProtocoleUdp().pack(&spawn);
    sendUdp(packed->getData(), packed->getSize(), RtypeProtocol::T_SPAWN);
    delete (packed);
  }

  void	Room::receive(const Game::Core& /*core*/,
		      const Game::CoreEvent::Destroy& event)
  {
    event.entity.deleteObserver(*this);
  }

  bool	Room::testConnection(const std::string& password) const
  {
    return (password == _pass);
  }

  bool	Room::isFull() const
  {
    return (_clients.size() == 4);
  }

  unsigned int	Room::getID() const
  {
    return (_id);
  }

  ClientRoom*	Room::addClient(ClientServer* clientserver, bool host)
  {
    ClientRoom*	clientroom = new ClientRoom(*this, *clientserver, host);

    _clients.push_back(clientroom);
    return (clientroom);
  }

  Game::Core&	Room::getGame()
  {
    return (_game);
  }

  void		Room::startGame()
  {
    _time = std::chrono::system_clock::now().time_since_epoch();
    _timer.setTimeout(duration_milli(0));
    _gamestarted = true;
  }

  void		Room::stopGame()
  {
    _timer.cancel();
    _gamestarted = false;
  }

  const std::string&	Room::getName() const
  {
    return (_name);
  }

  const std::list<ClientRoom*>&	Room::getClients() const
  {
    return (_clients);
  }

  bool	Room::isGameStarted() const
  {
    return (_gamestarted);
  }

  unsigned int	Room::getNbClient() const
  {
    return (_clients.size());
  }

  const std::string&	Room::getPass() const
  {
    return (_pass);
  }

  void			Room::close()
  {
    std::list<ClientRoom*>::iterator	it;

    for (it = _clients.begin(); it != _clients.end(); it++)
      {
	(*it)->getClientServer().sendHeader(RtypeProtocol::T_ROOM_HOST_LEAVED);
	(*it)->getClientServer().setClientRoom(NULL);
	(*it)->getClientServer().getServer().deleteClientRoom(*it);
      }
  }

  void			Room::deleteClient(ClientServer* clientserver)
  {
    _clients.remove(clientserver->getClientRoom());
  }

  bool			Room::isReady() const
  {
    std::list<ClientRoom*>::const_iterator	it;

    if (_clients.empty())
      return (false);

    for (it = _clients.begin(); it != _clients.end(); it++)
      {
	if ((*it)->getClientServer().getState() != ClientServer::T_INGAME)
	  return (false);
      }
    return (true);
  }

  void			Room::sendUdp(const void* data, size_t size, int type)
  {
    char				buffer[4096];
    RtypeProtocol::Header		header;
    Network::packet*			packed;
    std::list<ClientRoom*>::iterator	it;

    header.type = type;
    header.data_size = size;
    packed = _server.getProtocoleUdp().pack(&header);
    std::memcpy(buffer, packed->getData(), sizeof(header));
    std::memcpy(buffer + sizeof(header), data, size);
    std::cout << "Room::sendUdp" << std::endl;
    for (it = _clients.begin(); it != _clients.end(); it++)
      {
	std::cout << "loop" << std::endl;
	(*it)->getClientServer().sendUdp(buffer, size + sizeof(header));
      }
      delete packed;
  }
};
