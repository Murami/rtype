#include <cstring>
#include "ClientServer.hh"
#include "ClientException.hh"
#include "Server.hh"
#include "Util/Util.hh"
#include "ClientRoom.hh"

namespace Application
{

  Util::IDGenerator	Room::_generator = Util::IDGenerator();

  ClientServer::ClientServer(Server & server, Network::TcpSocket & socket) : _server(server), _socket(socket)
  {
    _socket.setObserver(this);
    _server.getService().addReadTcp(_socket);
    _server.getService().addWriteTcp(_socket);
    _state = T_MAGIC_WAITING;
  }

  ClientServer::~ClientServer() {}

  void	ClientServer::onRead(Network::TcpSocket & socket)
  {
    std::cout << "ClientServer::onRead()" << std::endl;
    _server.getService().addReadTcp(socket);
    try
      {
	_server.getProtocole().onRead(&socket, this);
      }
    catch (ClientException e)
      {
	std::cout << e.what() << std::endl;
	_server.deleteClientServer(this);
     }
  }

  void	ClientServer::onWrite(Network::TcpSocket & socket)
  {
    _server.getService().addWriteTcp(socket);
  }

  void	ClientServer::onTimeout(Network::Timer& timer)
  {
    // TIMEOUT DU CLIENT ON DECO TOUT !!!!!
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Magic * magicRcv, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_MAGIC)
      {
	std::cout << "magic" << std::endl;

	RtypeProtocol::Magic	magic;

	if (_state != T_MAGIC_WAITING)
	  throw ClientException("MAGIC PROTOCOL ERROR");

	magic.minor_version = RtypeProtocol::minor_version;
	magic.major_version = RtypeProtocol::major_version;
	std::memset(magic.proto_name, 0, PROTO_NAME_SIZE);
	std::memcpy(magic.proto_name, RtypeProtocol::proto_name, 5);

	std::cout << "minor " << magicRcv->minor_version << std::endl;
	std::cout << "major " << magicRcv->major_version << std::endl;

	if (std::memcmp(&magic, magicRcv, sizeof(RtypeProtocol::Magic)) != 0)
	  {
	    std::cout << "ERROR MAGIC" << std::endl;
	    this->sendHeader(RtypeProtocol::T_MAGIC_BAD_VERSION);
	  }
	else
	  {
	    std::cout << _state << std::endl;
	    std::cout << "PASSING TO DISCONNECTED STATE" << std::endl;
	    _state = T_DISCONNECTED;
	    std::cout << _state << std::endl;
	    this->sendHeader(RtypeProtocol::T_MAGIC_ACCEPT);
	  }
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::User * user, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_CONNECTION)
      {
	std::cout << "connection" << std::endl;

	std::cout << _state << std::endl;
	if (_state != T_DISCONNECTED)
	  throw ClientException("CONNECTION PROTOCOL ERROR");

	Util::stringncopy(_name, user->username, USERNAME_SIZE);
	_state = T_CONNECTED;
	this->sendHeader(RtypeProtocol::T_CONNECTION_OK);
	_server.sendAllRoomInfos(this);
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Message * msg, Network::TcpSocket *socket)
  {
    if (type == RtypeProtocol::T_MSG)
      {
	std::cout << "msg" << std::endl;
	if (_state != T_CONNECTED)
	  throw ClientException("PROTOCOL ERROR");

	// TODO send msg
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::RoomConnection * roomConnection,
			     Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_ROOM_JOIN)
      {
	std::cout << "room join" << std::endl;

	if (_state != T_CONNECTED)
	  throw ClientException("Join in non-connected state");

	Room*		room = _server.getRoom(roomConnection->id);
	std::string	pass;

	Util::stringncopy(pass, roomConnection->pass_md5, PASS_MD5_SIZE);

	if (room == NULL)			// NOT FOUND
	  {
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_NOT_FOUND);
	  }
	else if (!room->testConnection(pass))	// BAD PASS
	  {
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_BAD_PSWD);
	  }
	else if (room->isFull())		// IS FULL
	  {
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_IS_FULL);
	  }
	else if (room->isGameStarted())		// GAME ALREADY STARTED
	  {
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_STARTED);
	  }
	else					// OK
	  {
	    _state = T_INROOM;
	    _clientroom = room->addClient(this, false);
	    _server.addClientRoom(_clientroom);
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_OK);
	  }
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::PingPong * ping, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_PONG)
      {
	std::cout << "pong" << std::endl;

	_timer.setTimeout(std::chrono::duration<int, std::ratio<1> >(3));
	this->sendHeader(RtypeProtocol::T_PING);
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Room * room, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_ROOM_CREATE)
      {
	std::cout << "create room" << std::endl;

	std::string	roomname;

	if (_state != T_CONNECTED)
	  throw ClientException("Room creation in non-connected state");

	Util::stringncopy(roomname, room->room_name, ROOM_NAME_SIZE);

	if (_server.roomExists(roomname))
	  {
	    this->sendHeader(RtypeProtocol::T_ROOM_CREATE_ALREADY_EXIST);
	  }
	else
	  {
	    Room*	serverroom;

	    serverroom = _server.createRoom(this, room);
	    _server.sendRoomToAllClients(serverroom, true);
	    _clientroom = serverroom->addClient(this, true);
	    _server.addClientRoom(_clientroom);
	    _state = T_INROOM;
	    this->sendHeader(RtypeProtocol::T_ROOM_CREATE_OK);
	  }
      }
  }

  void	ClientServer::notify(int const &type, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_READY)
      {
	std::cout << "ready" << std::endl;

	if (_state != T_INROOM)
	  throw ClientException("");
      }
    if (type == RtypeProtocol::T_ROOM_EXIT)
      {
	std::cout << "room exit" << std::endl;

	if (_state != T_INROOM) // TODO leave en jeu aussi ? ...
	  throw ClientException("");

	Room*	room = _clientroom->getRoom();
	bool	isHost = _clientroom->isHost();

	room->deleteClient(this);
	_server.deleteClientRoom(_clientroom);
	_state = T_CONNECTED;
	this->sendHeader(RtypeProtocol::T_ROOM_EXIT_OK);
	if (_clientroom->isHost())
	    _server.sendRoomToAllClients(room, false);
	  {
	    _clientroom = NULL;
	    _server.deleteRoom(room);
	  }
      }
  }

  Network::TcpSocket & ClientServer::getSocket() const
  {
    return (_socket);
  }

  void	ClientServer::sendHeader(int type, unsigned int size)
  {
    RtypeProtocol::Header	header;

    header.type = type;
    header.data_size = size;
    send(this->_socket, header);
  }

  void	ClientServer::sendRoomInfos(const Room* room, bool alive)
  {
    RtypeProtocol::Room				roominfos;
    std::list<ClientRoom*>::const_iterator	it;

    roominfos.id = room->getID();
    roominfos.alive = alive;
    roominfos.locked = room->isGameStarted();
    roominfos.nb_connected_users = room->getNbClient();

    if (room->getPass() == "")
      roominfos.password_flag = 0;
    else
      roominfos.password_flag = 1;

    room->getName().copy(reinterpret_cast<char*>(roominfos.pass_md5), PASS_MD5_SIZE);
    room->getName().copy(reinterpret_cast<char*>(roominfos.room_name), ROOM_NAME_SIZE);

    for (it = room->getClients().begin(); it != room->getClients().end(); it++)
      {
	unsigned int	idx = std::distance(room->getClients().begin(), it);
	(*it)->getName().copy(reinterpret_cast<char*>(roominfos.ready_users[idx]), USERNAME_SIZE);
      }
    this->sendHeader(RtypeProtocol::T_ROOMINFO, sizeof(RtypeProtocol::Room));
    send(this->_socket, roominfos);
  }

  void	ClientServer::setClientRoom(ClientRoom* clientroom)
  {
    _clientroom = clientroom;
  }

  const std::string&	ClientServer::getName() const
  {
    return (_name);
  }

  Server&		ClientServer::getServer() const
  {
    return (_server);
  }

  ClientRoom*		ClientServer::getClientRoom() const
  {
    return (_clientroom);
  }
} /* namespace Application */
