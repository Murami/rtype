#include "ClientServer.hh"
#include "Server.hh"

namespace Application
{

  ClientServer::ClientServer(Server & server, Network::TcpSocket & socket) : _server(server), _socket(socket)
  {
    _socket.setObserver(this);
    _server.getService().addReadTcp(_socket);
    _server.getService().addWriteTcp(_socket);
  }

  ClientServer::~ClientServer() {}

  void	ClientServer::onRead(Network::TcpSocket & socket)
  {
    _server.getProtocole().onRead(&socket, this);
    _server.getService().addReadTcp(socket);
  }

  void	ClientServer::onWrite(Network::TcpSocket & socket)
  {
    _server.getService().addWriteTcp(socket);
  }

  void	ClientServer::notify(int const &type, const Network::Magic *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with Magic" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::User *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with User" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::Message *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with Message" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::RoomConnection *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with RoomConnection" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::PingPong *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with PingPong" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::Score *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with Score" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::MapChange *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with MapChange" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::GameReadyState *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with GameReadyState" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::EndGame *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with EndGame" << std::endl;
  }

  void	ClientServer::notify(int const &type, const Network::Room *, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with Room" << std::endl;
  }

  void	ClientServer::notify(int const &type, Network::TcpSocket *) const
  {
    std::cout << "rcv " << type << " with Nothing" << std::endl;
  }

  // void ClientServer::setRoom(Room * room)
  // {
  //   _room = room;
  // }

} /* namespace Application */
