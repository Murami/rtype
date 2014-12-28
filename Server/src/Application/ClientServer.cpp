#include <cstring>
#include "ClientServer.hh"
#include "ClientException.hh"
#include "Server.hh"
#include "Util/Util.hh"
#include "ClientRoom.hh"

namespace Application
{

  Util::IDGenerator	Room::_generator = Util::IDGenerator();

  ClientServer::ClientServer(Server & server, Network::TcpSocket & socket) :
    _server(server),
    _socket(socket)
  {
    _socket.setObserver(this);
    _server.getService().addReadTcp(_socket);
    _server.getService().addWriteTcp(_socket);
    _state = T_MAGIC_WAITING;
    _clientroom = NULL;
  }

  ClientServer::~ClientServer() {
    if (_clientroom)
    {
      _clientroom->getRoom()->deleteClient(this);
    }
  }

  /////////////////////////////
  /// Network notifications ///
  /////////////////////////////

  void	ClientServer::onRead(Network::TcpSocket & socket, const bool error)
  {
    if (error)
    {
      _server.deleteClientServer(this);
      return ;
    }
    // std::cout << "ClientServer::onRead()" << std::endl;
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

  void	ClientServer::onTimeout(Network::Timer&)
  {
    // TIMEOUT DU CLIENT ON DECO TOUT !!!!!
  }

  //////////////////////////////
  /// Protocol notifications ///
  //////////////////////////////

  void	ClientServer::notify(int const &type, const RtypeProtocol::Magic * magicRcv,
			     Network::TcpSocket *)
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

	if (std::memcmp(&magic, magicRcv, sizeof(RtypeProtocol::Magic)) != 0)
	  {
	    std::cout << "ERROR MAGIC" << std::endl;
	    this->sendHeader(RtypeProtocol::T_MAGIC_BAD_VERSION);
	  }
	else
	  {
	    std::cout << _state << std::endl;
	    _state = T_DISCONNECTED;
	    std::cout << _state << std::endl;
	    this->sendHeader(RtypeProtocol::T_MAGIC_ACCEPT);
	  }
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::User * user,
			     Network::TcpSocket *)
  {
    if (type == RtypeProtocol::T_CONNECTION)
      {
	std::cout << "connection" << std::endl;

	std::cout << _state << std::endl;
	if (_state != T_DISCONNECTED)
	  throw ClientException("CONNECTION PROTOCOL ERROR");
  std::cout << "client in connection" << std::endl;

	Util::stringncopy(_name, user->username, USERNAME_SIZE);
	_udpport = user->port;

	_state = T_CONNECTED;
	this->sendHeader(RtypeProtocol::T_CONNECTION_OK);
	_server.sendAllRoomInfos(this);
	std::cout << "client connected" << std::endl;
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Message * msg,
			     Network::TcpSocket *)
  {
    if (type == RtypeProtocol::T_MSG)
      {
	std::cout << "msg : " << msg->message << std::endl;
	if (_state != T_CONNECTED)
	  throw ClientException("PROTOCOL ERROR");

	// TODO send msg
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::RoomConnection * roomConnection,
			     Network::TcpSocket *)
  {
    if (type == RtypeProtocol::T_ROOM_JOIN)
      {
	std::cout << "##### ROOM JOIN #####" << std::endl;

	if (_state != T_CONNECTED)
	  throw ClientException("Join in non-connected state");

	Room*		room = _server.getRoom(roomConnection->id);
	std::string	pass;

	Util::stringncopy(pass, roomConnection->pass_md5, PASS_MD5_SIZE);

	if (room == NULL)			// NOT FOUND
	  {
	    std::cout << "-> not found" << std::endl;
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_NOT_FOUND);
	  }
	else if (!room->testConnection(pass))	// BAD PASS
	  {
	    std::cout << "-> bad password" << std::endl;
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_BAD_PSWD);
	  }
	else if (room->isFull())		// IS FULL
	  {
	    std::cout << "-> is full" << std::endl;
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_IS_FULL);
	  }
	else if (room->isGameStarted())		// GAME ALREADY STARTED
	  {
	    std::cout << "-> started " << std::endl;
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_STARTED);
	  }
	else					// OK
	  {
	    _state = T_INROOM;
	    _clientroom = room->addClient(this, false);
	    _server.addClientRoom(_clientroom);
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_OK);
	    _clientroom->updateRoomInfos();
	  }
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::PingPong *, Network::TcpSocket *)
  {
    if (type == RtypeProtocol::T_PONG)
      {
	std::cout << "pong" << std::endl;

	_timer.setTimeout(std::chrono::duration<int, std::ratio<1> >(3));
	this->sendHeader(RtypeProtocol::T_PING);
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Room * room, Network::TcpSocket *)
  {
    if (type == RtypeProtocol::T_ROOM_CREATE)
      {
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
      if (!serverroom)
        return ;
	    _server.sendRoomToAllClients(serverroom, true);
	    _clientroom = serverroom->addClient(this, true);
	    _server.addClientRoom(_clientroom);
	    _state = T_INROOM;
	    this->sendHeader(RtypeProtocol::T_ROOM_CREATE_OK);
	    _clientroom->updateRoomInfos();
	  }
      }
  }

  void	ClientServer::notify(int const &type, Network::TcpSocket *)
  {
    if (type == RtypeProtocol::T_READY)
    {
      std::cout << "ready" << std::endl;

      if (_state != T_INROOM)
      throw ClientException("Not in room");
      _state = T_INGAME;
      if (_clientroom->getRoom()->isReady())
      {
        _clientroom->getRoom()->startGame();
        _clientroom->getRoom()->sendGameStart();
      }
      _clientroom->addToGame();
    }
    if (type == RtypeProtocol::T_ROOM_EXIT)
    {
      Room*	room;

      std::cout << "room exit" << std::endl;
      room = _clientroom->getRoom();
      _server.deleteClientRoom(_clientroom);

      if (_state != T_INROOM && _state != T_INGAME)
        throw ClientException("Not in a room or game");

      if (room->getNbClient() != 1)
	{
	  room->updateRoomInfos();
	}
      else
	{
	  this->sendRoomInfos(room, false);
	}
      _clientroom->getRoom()->deleteClient(this);
      _clientroom = NULL;
      _state = T_CONNECTED;

    }
  }

  ///////////////
  /// Getters ///
  ///////////////

  Network::TcpSocket&	ClientServer::getSocket() const
  {
    return (_socket);
  }

  ClientRoom*		ClientServer::getClientRoom() const
  {
    return (_clientroom);
  }

  const std::string&	ClientServer::getName() const
  {
    return (_name);
  }

  Server&		ClientServer::getServer() const
  {
    return (_server);
  }

  ClientServer::State	ClientServer::getState() const
  {
    return (_state);
  }

  const std::string&	ClientServer::getIP() const
  {
    return (_socket.getIP());
  }

  unsigned short	ClientServer::getPort() const
  {
    return (_udpport);
  }

  ///////////////
  /// Setters ///
  ///////////////

  void	ClientServer::setClientRoom(ClientRoom* clientroom)
  {
    _clientroom = clientroom;
  }

  ///////////////
  /// Senders ///
  ///////////////

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

    std::memset(&roominfos, 0, sizeof(RtypeProtocol::Room));

    roominfos.id = room->getID();
    roominfos.alive = alive;
    roominfos.locked = room->isGameStarted();
    roominfos.nb_connected_users = room->getNbClient();

    if (room->getPass() == "")
      roominfos.password_flag = 0;
    else
      roominfos.password_flag = 1;

    room->getPass().copy(reinterpret_cast<char*>(roominfos.pass_md5), PASS_MD5_SIZE);
    room->getName().copy(reinterpret_cast<char*>(roominfos.room_name), ROOM_NAME_SIZE);

    for (it = room->getClients().begin(); it != room->getClients().end(); it++)
      {
	unsigned int	idx = std::distance(room->getClients().begin(), it);
	(*it)->getName().copy(reinterpret_cast<char*>(roominfos.connected_users[idx]),
			      USERNAME_SIZE);
      }
    this->sendHeader(RtypeProtocol::T_ROOMINFO, sizeof(RtypeProtocol::Room));
    send(this->_socket, roominfos);
  }

  void	ClientServer::sendUdp(const void* data, size_t size)
  {
    _server.sendUdp(*this, data, size);
  }

  void	ClientServer::sendGameEnd(bool victory)
  {
    RtypeProtocol::EndGame	end;

    end.victory = victory;
    this->sendHeader(RtypeProtocol::T_GAMEEND, sizeof(RtypeProtocol::EndGame));
    send(this->_socket, end);
  }

  void	ClientServer::setState(State state)
  {
    _state = state;
  }

} /* namespace Application */
