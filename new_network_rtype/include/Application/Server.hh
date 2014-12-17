#ifndef SERVER_HH
# define SERVER_HH

#include "Service.hh"
#include "Acceptor.hh"
#include "AcceptorObserver.hh"
#include "UdpSocket.hh"
#include "UdpSocketObserver.hh"
#include "ClientServer.hh"

namespace Application
{

  class Server : Network::AcceptorObserver, public Network::UdpSocketObserver
  {
  public:
    Server(Network::Service & service);
    ~Server();

    void run();
    void onAccept(Network::Acceptor & socket);
    void onRead(Network::UdpSocket & socket);
    void onWrite(Network::UdpSocket & socket);

    Network::Service & getService() const;

  private:
    Network::Service &			_service;

    Network::Acceptor			_acceptor;
    Network::UdpSocket			_udpSocket;

    std::list<ClientServer*>		_clients;
    // std::list<Room*>			_rooms;
  };

} /* namespace Application */

#endif /* SERVER_HH */
