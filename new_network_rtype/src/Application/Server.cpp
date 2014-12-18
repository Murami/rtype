#include "Server.hh"

namespace Application
{

  Server::Server(Network::Service & service) : _service(service), _acceptor(3278)
  {
    _acceptor.setObserver(this);
    _udpSocket.setObserver(this);

    _service.addAcceptor(_acceptor);
    _service.addReadUdp(_udpSocket);
    _service.addWriteUdp(_udpSocket);

    _timer1.setObserver(this);
    _timer1.setTimeout(Network::duration_millisecond(100));
    _service.addTimeout(_timer1);
  }

  Server::~Server()
  {

  }

  void Server::run()
  {
    _service.run();
  }

  void Server::onAccept(Network::Acceptor & acceptor)
  {
    Network::TcpSocket * clientSocket;

    acceptor.acceptSocket();
    clientSocket = acceptor.getAcceptSocket();
    ClientServer* client = new ClientServer(*this, *clientSocket);
    _clients.push_front(client);

    _service.addAcceptor(acceptor);
  }

  void Server::onRead(Network::UdpSocket & socket)
  {
    _service.addReadUdp(socket);
  }

  void Server::onWrite(Network::UdpSocket & socket)
  {
    _service.addReadUdp(socket);
  }

  void Server::onTimeout(Network::Timer & timer)
  {
    timer.setTimeout(Network::duration_millisecond(100));
    _service.addTimeout(timer);
  }

  Network::Service & Server::getService() const
  {
    return (_service);
  }

  const Network::ProtocoleTcp & Server::getProtocole() const
  {
    return (_protocoleTcp);
  }

}
