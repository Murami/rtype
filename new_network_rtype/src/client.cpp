#include <iostream>
#include "Service.hh"
#include "TcpSocket.hh"
#include "UdpSocket.hh"
#include "TcpSocketObserver.hh"
#include "UdpSocketObserver.hh"

using namespace Network;

class Client : public TcpSocketObserver
{
private:
  Service & _service;
  TcpSocket _socketTCP;

public:
  Client(Service & service) : _service(service), _socketTCP(3278, "127.0.0.1")
  {
    _socketTCP.setObserver(this);
    _service.addWriteTcp(_socketTCP);
    _service.addReadTcp(_socketTCP);
  }

  ~Client()
  {

  }

  void onWrite(TcpSocket& socket)
  {
    _service.addWriteTcp(_socketTCP);
  }

  void onRead(TcpSocket& socket)
  {
    _service.addReadTcp(_socketTCP);
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
