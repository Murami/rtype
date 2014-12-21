#include <algorithm>
#include "Server.hh"
#include "Util/Util.hh"
#include "RtypeProtocol.hh"
#include "Application/ClientRoom.hh"

namespace Application
{
  Server::Server(Network::Service & service) : _service(service), _acceptor(RtypeProtocol::TcpPort)
  {
    std::cout << "server start" << std::endl;
    _acceptor.setObserver(this);
    _udpSocket.setObserver(this);

    _service.addAcceptor(_acceptor);
    _service.addReadUdp(_udpSocket);
    _service.addWriteUdp(_udpSocket);

    _timer1.setObserver(this);
    _timer1.setTimeout(Network::duration_millisecond(100));
    _service.addTimeout(_timer1);
  }

  Server::~Server()
  {
    std::cout << "server end" << std::endl;
  }

  void Server::run()
  {
    _service.run();
  }

  // Network events
  void Server::onAccept(Network::Acceptor & acceptor)
  {
    std::cout << "accept" << std::endl;
    Network::TcpSocket * clientSocket;

    acceptor.acceptSocket();
    clientSocket = acceptor.getAcceptSocket();
    ClientServer* client = new ClientServer(*this, *clientSocket);
    _clients.push_front(client);

    _service.addAcceptor(acceptor);
  }

  void Server::onRead(Network::UdpSocket & socket)
  {
    _protocoleUdp.onRead(&socket, this);
    _service.addReadUdp(socket);
  }

  void Server::onWrite(Network::UdpSocket & socket)
  {
    _service.addReadUdp(socket);
  }

  void Server::onTimeout(Network::Timer & timer)
  {
    timer.setTimeout(Network::duration_millisecond(100));
    _service.addTimeout(timer);
  }

  // ClientServer
  void Server::deleteClientServer(ClientServer * client)
  {
    _service.deleteReadTcp(client->getSocket());
    _service.deleteWriteTcp(client->getSocket());
    _clients.erase(std::find(_clients.begin(), _clients.end(), client));
    delete client;
    /* WARNNNNNNNING delete les timeout, l'objet MUST BE un timerObserver*/ /* HAHAHAHAHA MUST BE XD */
    /* delete les udp aussi */
  }

  // Room
  Room* Server::createRoom(ClientServer *, const RtypeProtocol::Room* roominfos)
  {
    std::string	name;
    std::string	pass;

    Util::stringncopy(name, roominfos->room_name, ROOM_NAME_SIZE);
    Util::stringncopy(pass, roominfos->pass_md5, PASS_MD5_SIZE);

    Room*	room = new Room(*this, name, pass);

    std::cout << "Create room aaaaaaaaaaaaaaaaaaaaaa" << std::endl;

    _rooms.insert(std::pair<unsigned int, Room *>(room->getID(), room));
    return (room);
  }

  Room*	Server::getRoom(unsigned int roomID) const
  {
    if (_rooms.find(roomID) == _rooms.end())
      return (NULL);
    return (_rooms.at(roomID));
  }

  bool	Server::roomExists(const std::string& name) const
  {
    std::map<unsigned int, Room*>::const_iterator	it;

    for (it = _rooms.begin(); it != _rooms.end(); it++)
    {
      std::cout << it->second->getName() << std::endl;
      if ((it->second)->getName() == name)
	return (true);
}
    return (false);
  }

  // Get composite objects
  Network::Service &		Server::getService() const
  {
    return (_service);
  }

  const Network::ProtocoleTcp & Server::getProtocole() const
  {
    return (_protocoleTcp);
  }

  void	Server::addClientRoom(ClientRoom* clientroom)
  {
    std::string	ip = clientroom->getClientServer().getIP();

    _clientsroom[ip] = clientroom;
  }

  void	Server::deleteClientRoom(ClientRoom* clientroom)
  {
    _clientsroom.erase(clientroom->getClientServer().getIP());
  }

  void	Server::sendAllRoomInfos(ClientServer* clientserver) const
  {
    std::map<unsigned int, Room*>::const_iterator	it;

    std::cout << "send all room infos" << std::endl;
    for (it = _rooms.begin(); it != _rooms.end(); it++)
      {
	std::cout << "send one room" << std::endl;
	clientserver->sendRoomInfos(it->second, true);
      }
  }

  void	Server::sendRoomToAllClients(const Room* room, bool alive)
  {
    std::list<ClientServer*>::iterator	it;

    for (it = _clients.begin(); it != _clients.end(); it++)
      (*it)->sendRoomInfos(room, alive);
  }

  void	Server::deleteRoom(Room* room)
  {
    std::map<unsigned int, Room*>::iterator	it;

    for (it = _rooms.begin(); it != _rooms.end(); it++)
      {
	if (it->second == room)
	  {
	    room->close();
	    delete (room);
	    _rooms.erase(it);
	    return;
	  }
      }
  }

  void	Server::notify(int const &, const RtypeProtocol::State* state, const unsigned int &, const std::string& host)
  {
    std::cout << "UDP state" << std::endl;
    if (_clientsroom.find(host) == _clientsroom.end())
      throw (std::runtime_error("Invalid peer")); // TODO a catch et faire une exception server
    _clientsroom[host]->notify(state);
  }

  void	Server::notify(int const &, const RtypeProtocol::EntityRequest* request, const unsigned int &, const std::string& host)
  {
    std::cout << "UDP request" << std::endl;
    if (_clientsroom.find(host) == _clientsroom.end())
      throw (std::runtime_error("Invalid peer")); // TODO a catch et faire une exception server
    _clientsroom[host]->notify(request);
  }
}
