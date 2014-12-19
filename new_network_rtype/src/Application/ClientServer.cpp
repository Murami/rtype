#include <cstring>
#include "ClientServer.hh"
#include "ClientException.hh"
#include "Server.hh"

namespace Application
{

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
    std::cout << "rcv " << type << " with Magic" << std::endl;
    RtypeProtocol::Header header;
    RtypeProtocol::Magic magic;

    magic.minor_version = RtypeProtocol::minor_version;
    magic.major_version = RtypeProtocol::major_version;
    std::memset(magic.proto_name, 0, PROTO_NAME_SIZE);
    std::memcpy(magic.proto_name, RtypeProtocol::proto_name, 5); /* attention */
    if (std::memcmp(&magic, magicRcv, sizeof(RtypeProtocol::Magic)) != 0)
      {
	header.type = RtypeProtocol::T_MAGIC_BAD_VERSION;
	header.data_size = 0;
	throw ClientException("MAGIC ERROR");
      }
    else
      {
	_state = T_DISCONNECTED;
	header.type = RtypeProtocol::T_MAGIC_ACCEPT;
	header.data_size = 0;
      }

    Network::packet * packet = _server.getProtocole().pack(&header);
    _socket.sendData(packet->getData(), packet->getSize());
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::User * user, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with User" << std::endl;

    if (_state != T_DISCONNECTED)
      throw ClientException("PROTOCOL ERROR");

    // if (type == RtypeProtocol::T_PLAYERINFO)
    //   {
    // 	//
    //   }
    if (type == RtypeProtocol::T_CONNECTION)
      {
	_state = T_CONNECTED;
	_name = std::string(reinterpret_cast<const char*>(user->username),
			    strnlen(reinterpret_cast<const char*>(user->username), USERNAME_SIZE));
	// TODO send ok connection
      }
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::Message * msg, Network::TcpSocket *socket)
  {
    if (_state != T_CONNECTED)
      throw ClientException("PROTOCOL ERROR");

    // PAS DE GESTION DE MESSAGE POUR L'INSTANT
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::RoomConnection * roomConnection,
			     Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with RoomConnection" << std::endl;
  }

  void	ClientServer::notify(int const &type, const RtypeProtocol::PingPong * ping, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with PingPong" << std::endl;
  }

  // A ENLEVER
  void	ClientServer::notify(int const &type, const RtypeProtocol::Score * score, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with Score" << std::endl;
  }

  // A ENLEVER
  void	ClientServer::notify(int const &type, const RtypeProtocol::MapChange * map, Network::TcpSocket *socket)
  {
    std::cout << "rcv " << type << " with MapChange" << std::endl;
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

  // void ClientServer::setRoom(Room * room)
  // {
  //   _room = room;
  // }

} /* namespace Application */
