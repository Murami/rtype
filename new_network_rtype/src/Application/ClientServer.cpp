#include <cstring>
#include "ClientServer.hh"
#include "ClientException.hh"
#include "Server.hh"
#include "Util/Util.hh"

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

  void	ClientServer::notify(int const &type, const RtypeProtocol::Magic * magicRcv, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_MAGIC)
      {
	RtypeProtocol::Header header;
	RtypeProtocol::Magic magic;

	if (_state != T_MAGIC_WAITING)
	  throw ClientException("PROTOCOL ERROR");

	magic.minor_version = RtypeProtocol::minor_version;
	magic.major_version = RtypeProtocol::major_version;
	std::memset(magic.proto_name, 0, PROTO_NAME_SIZE);
	std::memcpy(magic.proto_name, RtypeProtocol::proto_name, 5); /* attention */

	if (std::memcmp(&magic, magicRcv, sizeof(RtypeProtocol::Magic)) != 0)
	  {
	    this->sendHeader(RtypeProtocol::T_MAGIC_BAD_VERSION);
	  }
	else
	  {
	    _state = T_DISCONNECTED;
	    this->sendHeader(RtypeProtocol::T_MAGIC_ACCEPT);
	  }
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::User * user, Network::TcpSocket * socket)
  {
    if (type == RtypeProtocol::T_CONNECTION)
      {
	if (_state != T_DISCONNECTED)
	  throw ClientException("PROTOCOL ERROR");

	Util::stringncopy(_name, user->username, USERNAME_SIZE);
	_state = T_CONNECTED;
	this->sendHeader(RtypeProtocol::T_CONNECTION_OK);
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Message * msg, Network::TcpSocket *socket)
  {
    if (type == RtypeProtocol::T_MSG)
      {
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
	else					// OK
	  {
	    _clientroom = room->addClient(this);
	    _server.addClientRoom(_clientroom);
	    this->sendHeader(RtypeProtocol::T_ROOM_JOIN_OK);
	  }
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::PingPong * ping, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with PingPong" << std::endl;
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::GameReadyState * state,
			     Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with GameReadyState" << std::endl;
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::EndGame * end, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with EndGame" << std::endl;
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Room * room, Network::TcpSocket * socket)
  {
    if (_state != T_CONNECTED)
      throw ClientException("PROTOCOL ERROR");
    _server.createRoom(this, room);
  }

  void	ClientServer::notify(int const &type, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with Nothing" << std::endl;
  }

  Network::TcpSocket & ClientServer::getSocket() const
  {
    return (_socket);
  }

  void	ClientServer::sendHeader(int type)
  {
    RtypeProtocol::Header	header;

    header.type = type;
    header.type = 0;
    send(this->_socket, header);
  }

  void	ClientServer::setClientRoom(ClientRoom* clientroom)
  {
    _clientroom = clientroom;
  }

  // void ClientServer::setRoom(Room * room)
  // {
  //   _room = room;
  // }

} /* namespace Application */
