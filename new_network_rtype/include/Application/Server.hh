#ifndef SERVER_HH
# define SERVER_HH

#include "Service.hh"
#include "Acceptor.hh"
#include "AcceptorObserver.hh"
#include "UdpSocket.hh"
#include "UdpSocketObserver.hh"
#include "Timer.hh"
#include "TimerObserver.hh"
#include "ClientServer.hh"
#include "Protocole.hh"

#define MINOR_VERSION 1.0
#define MAJOR_VERSION 1.0
#define PROTO_NAME "rtype"

namespace Application
{
  class Server : Network::AcceptorObserver, public Network::UdpSocketObserver, public Network::TimerObserver
  {
  public:
    Server(Network::Service & service);
    ~Server();

    void				run();
    void				onAccept(Network::Acceptor & socket);
    void				onRead(Network::UdpSocket & socket);
    void				onWrite(Network::UdpSocket & socket);
    void				onTimeout(Network::Timer & timer);

    void				deleteClientServer(ClientServer * client);

    Network::Service &			getService() const;
    const Network::ProtocoleTcp &	getProtocole() const;

  private:
    Network::Service &			_service;
    Network::ProtocoleTcp		_protocoleTcp;

    Network::Acceptor			_acceptor;
    Network::UdpSocket			_udpSocket;

    std::list<ClientServer*>		_clients;
    // std::list<Room*>			_rooms;

    Network::Timer			_timer1;
  };

} /* namespace Application */

#endif /* SERVER_HH */