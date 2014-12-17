#include "UdpSocket.hh"
#include "UdpSocketObserver.hh"
#include "NetworkException.hh"

namespace Network
{

  UdpSocket::UdpSocket()
  {
    _socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(_socket == INVALID_SOCKET)
      throw NetworkException("udp socket initialization failed");
  }

  UdpSocket::~UdpSocket()
  {
    closesocket(_socket);
  }

  SOCKET UdpSocket::getSocket()
  {
    return (_socket);
  }

  void UdpSocket::sendDataTo(const void *data, int size, unsigned int port, const std::string & host)
  {
    SOCKADDR_IN to = { 0 };

    to.sin_addr.s_addr = inet_addr(host.c_str());
    to.sin_port = htons(port);
    to.sin_family = AF_INET;

    unsigned int tosize = sizeof to;

    if(sendto(_socket, data, size, 0, (SOCKADDR *)&to, tosize) < 0)
      throw NetworkException("udp socket sendto failed");
  }

  int UdpSocket::recvDataFrom(void *data, int size, unsigned int & port, std::string & host)
  {
    int	n;
    SOCKADDR_IN from = { 0 };
    unsigned int fromsize = sizeof from;

    if((n = recvfrom(_socket, data, size, 0, (SOCKADDR *)&from, &fromsize)) < 0)
      throw NetworkException("udp socket recvfrom failed");
    port = from.sin_port;
    host = inet_ntoa(from.sin_addr);
    return (n);
  }

  void UdpSocket::bindSocket(unsigned int port)
  {
    SOCKADDR_IN sin = { 0 };

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    if (bind(_socket, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
      throw NetworkException("udp socket bind failed");
  }

  void	UdpSocket::setObserver(UdpSocketObserver * observer)
  {
    _observer = observer;
  }

  void	UdpSocket::notifyRead()
  {
    _observer->onRead(this);
  }

  void	UdpSocket::notifyWrite()
  {
    _observer->onWrite(this);
  }

} /* namespace Network */
