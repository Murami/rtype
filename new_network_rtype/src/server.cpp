#include <iostream>
#include "Service.hh"
#include "Acceptor.hh"
#include "TcpSocket.hh"
#include "UdpSocket.hh"
#include "Timer.hh"
#include "AcceptorObserver.hh"
#include "TcpSocketObserver.hh"
#include "UdpSocketObserver.hh"
#include "TimerObserver.hh"

using namespace Network;

class Server : public AcceptorObserver, public TcpSocketObserver, public UdpSocketObserver, public TimerObserver
{
private:
  Service & _service;
  Acceptor  _acceptor;
  TcpSocket * _client;
  UdpSocket _udp;
  Timer		_timeout1;
  Timer		_timeout2;
  Timer		_timeout3;
  Timer		_timeout4;

public:
  Server(Service & service) : _service(service), _acceptor(4242)
  {
    _acceptor.setObserver(this);
    _service.addAcceptor(_acceptor);

    // _udp.setObserver(this);
    // _service.addReadUdp(_udp);
    // _udp.bindSocket(1234);

    _timeout1.setTime(2, 0);
    _timeout1.setObserver(this);
    _service.addTimeout(_timeout1);
    _timeout2.setTime(4, 0);
    _timeout2.setObserver(this);
    _service.addTimeout(_timeout2);
    _timeout3.setTime(8, 0);
    _timeout3.setObserver(this);
    _service.addTimeout(_timeout3);
    _timeout4.setTime(16, 0);
    _timeout4.setObserver(this);
    _service.addTimeout(_timeout4);
  }

  ~Server()
  {

  }

  void run()
  {
    _service.run();
  }

  void onAccept(Acceptor * socket)
  {
    std::cout << "on accept detected" << std::endl;
    socket->acceptSocket();
    _client = socket->getAcceptSocket();
    _client->setObserver(this);

    _service.addReadTcp(*_client);
    _service.addWriteTcp(*_client);
    _service.addAcceptor(*socket);

    _client->sendData("coucou", 6);
  }

  void onRead(TcpSocket* socket)
  {

    int size = socket->availableDataOnRead();
    char* buffer = new char[size];

    socket->readData(buffer, size);

    std::cout << "on read = " << std::string(buffer, size) << std::endl;
    _service.addReadTcp(*socket);
  }

  void onWrite(TcpSocket* socket)
  {
    _service.addWriteTcp(*socket);
  }

  void onRead(UdpSocket* socket)
  {
    int size = 4096;
    unsigned int port;
    std::string host;
    char* buffer = new char[size];

    size = socket->recvDataFrom((void*)buffer, size, port, host);
    std::cout << "on read = " << std::string(buffer, size) << std::endl;
    _service.addReadUdp(*socket);
    socket->sendDataTo("coucou je suis le server", sizeof("coucou je suis le server"), 1235, "127.0.0.1");
  }

  void onWrite(UdpSocket* socket)
  {
    _service.addWriteUdp(*socket);
  }

  void onTimeout(Timer *timeout)
  {
    std::cout << "timeout detected" << std::endl;
    //_service.addTimeout(*timeout);
  }

};

int main()
{
  Service service;
  Server server(service);

  server.run();
  return (0);
}
