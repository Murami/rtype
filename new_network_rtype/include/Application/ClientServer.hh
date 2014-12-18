#ifndef CLIENT_SERVER_HH
# define CLIENT_SERVER_HH

#include "TcpSocket.hh"
#include "TcpSocketObserver.hh"
#include "ProtocoleObserver.hh"
// #include "Room.hh"

namespace Application
{
  class Server;

  class ClientServer : public Network::TcpSocketObserver, public Network::ITcpProtocoleObserver
  {
  public:
    ClientServer(Server & server, Network::TcpSocket & socket);
    ~ClientServer();

    void			onRead(Network::TcpSocket & socket);
    void			onWrite(Network::TcpSocket & socket);

    // void			setRoom(Room * room);

  private:
    Server &			_server;
    Network::TcpSocket &	_socket;
    // Room *			_room;
  };

} /* namespace Application */

#endif /* CLIENT_SERVER_HH */
