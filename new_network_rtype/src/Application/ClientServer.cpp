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
    _server.getService().addReadTcp(socket);
  }

  void	ClientServer::onWrite(Network::TcpSocket & socket)
  {
    _server.getService().addWriteTcp(socket);
  }

  // void ClientServer::setRoom(Room * room)
  // {
  //   _room = room;
  // }

} /* namespace Application */
