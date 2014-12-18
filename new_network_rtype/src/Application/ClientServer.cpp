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
    _server.getProtocole().onRead(socket, this);
    _server.getService().addReadTcp(socket);
  }

  void	ClientServer::onWrite(Network::TcpSocket & socket)
  {
    _server.getService().addWriteTcp(socket);
  }

  void	notify(int const &type, const Network::Magic *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::User *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::Message *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::RoomConnection *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::PingPong *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::Score *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::MapChange *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::GameReadyState *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::EndGame *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, const Network::Room *, Network::TcpSocket *) const
  {

  }

  void	notify(int const &type, Network::TcpSocket *) const
  {

  }

  // void ClientServer::setRoom(Room * room)
  // {
  //   _room = room;
  // }

} /* namespace Application */
