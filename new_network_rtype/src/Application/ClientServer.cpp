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

  void	ClientServer::notify(int const &type, const Network::Magic * magic, Network::TcpSocket * socket)
  {
    Network::Header header;

    std::cout << "rcv " << type << " with Magic" << std::endl;

    if (magic->minor_version != MINOR_VERSION || magic->major_version != MAJOR_VERSION ||
	std::string((char*)magic->proto_name, PROTO_NAME_SIZE) != std::string(PROTO_NAME, PROTO_NAME_SIZE))
      {
	header.type = Network::T_MAGIC_BAD_VERSION;
	header.data_size = 0;
	throw ClientException("MAGIC ERROR");
      }
    else
      {
	_state = T_DISCONNECTED;
	header.type = Network::T_MAGIC_ACCEPT;
	header.data_size = 0;
      }

    Network::packet * packet = _server.getProtocole().pack(&header);
    _socket.sendData(packet->getData(), packet->getSize());
  }

  void	ClientServer::notify(int const &type, const Network::User * user, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with User" << std::endl;

    if (_state != T_DISCONNECTED)
      {
	/* error */
      }
  }

  void	ClientServer::notify(int const &type, const Network::Message * msg, Network::TcpSocket *socket)
  {
    std::cout << "rcv " << type << " with Message" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::RoomConnection * roomConnection,
			     Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with RoomConnection" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::PingPong * ping, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with PingPong" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::Score * score, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with Score" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::MapChange * map, Network::TcpSocket *socket)
  {
    std::cout << "rcv " << type << " with MapChange" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::GameReadyState * state,
			     Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with GameReadyState" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::EndGame * end, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with EndGame" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::Room * room, Network::TcpSocket * socket)
  {
    std::cout << "rcv " << type << " with Room" << std::endl;
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
