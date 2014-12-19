#include <iostream>
#include "Service.hh"
#include "TcpSocket.hh"
#include "UdpSocket.hh"
#include "TcpSocketObserver.hh"
#include "UdpSocketObserver.hh"
#include "Protocole.hh"
# include <cstring>

using namespace Network;

class Client : public TcpSocketObserver
{
private:
  Service &	_service;
  TcpSocket	_socketTCP;
  ProtocoleTcp	_protocole;

public:
  Client(Service & service) : _service(service), _socketTCP(3278, "127.0.0.1")
  {
    _socketTCP.setObserver(this);
    _service.addWriteTcp(_socketTCP);
    _service.addReadTcp(_socketTCP);

    RtypeProtocol::Header header;
    RtypeProtocol::Magic magic;

    header.type = RtypeProtocol::T_MAGIC;
    header.data_size = sizeof(RtypeProtocol::Magic);
    magic.minor_version = RtypeProtocol::minor_version;
    magic.major_version = RtypeProtocol::major_version;
    std::memset(magic.proto_name, 0, PROTO_NAME_SIZE);
    std::memcpy(magic.proto_name, RtypeProtocol::proto_name, 5);

    Network::packet * packet = _protocole.pack(&header);
    Network::packet * m_packet = _protocole.pack(&magic);

    _socketTCP.sendData(packet->getData(), packet->getSize());
    _socketTCP.sendData(m_packet->getData(), m_packet->getSize());
    delete packet;
    delete m_packet;
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
