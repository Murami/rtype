#include <iostream>
#include "Service.hh"
#include "TcpSocket.hh"
#include "UdpSocket.hh"
#include "TcpSocketObserver.hh"
#include "UdpSocketObserver.hh"

using namespace Network;

class Client : public TcpSocketObserver, public UdpSocketObserver
{
private:
  Service & _service;
  TcpSocket _socketTCP;
  UdpSocket _udp;

public:
  Client(Service & service) : _service(service), _socketTCP(4242, "127.0.0.1")
  {
    _socketTCP.setObserver(this);
    _service.addWriteTcp(_socketTCP);
    _service.addReadTcp(_socketTCP);

    // _udp.setObserver(this);
    // _service.addReadUdp(_udp);
    // _udp.bindSocket(1235);
    //    _udp.sendDataTo("coucou je suis le client", sizeof("coucou je suis le client"), 1234, "127.0.0.1");
  }

  ~Client()
  {

  }

  void onWrite(TcpSocket* socket)
  {
    _service.addWriteTcp(_socketTCP);
  }

  void onRead(TcpSocket* socket)
  {
    int size = socket->availableDataOnRead();
    char* buffer = new char[size];

    socket->readData(buffer, size);
    std::cout << "on read =" << buffer << std::endl;
    _service.addReadTcp(*socket);

    socket->sendData("salut toi", 9);
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
    socket->sendDataTo("coucou je suis le client", sizeof("coucou je suis le client"), 1234, "127.0.0.1");
  }

  void onWrite(UdpSocket* socket)
  {
    _service.addWriteUdp(*socket);
  }

  void run()
  {
    _service.run();
  }
};

int main()
{
  Service service;
  Client client(service);

  client.run();
  return (0);
}
