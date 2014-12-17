#include <cstring>
#include "TcpSocket.hh"
#include "Acceptor.hh"
#include "AcceptorObserver.hh"
#include "NetworkException.hh"

namespace Network
{

  Acceptor::Acceptor(unsigned int port)
  {
    SOCKADDR_IN sin;

    memset(&sin, 0, sizeof(sin));
    _asocket = socket(AF_INET, SOCK_STREAM, 0);

    if(_asocket == INVALID_SOCKET)
      throw NetworkException("Acceptor initialization failed");

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    if(bind (_asocket, (SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
      throw NetworkException("Acceptor bind failed");

    if(listen(_asocket, 5) == SOCKET_ERROR)
      throw NetworkException("Acceptor listen failed");
  }

  Acceptor::~Acceptor()
  {
    closesocket(_asocket);
  }

  SOCKET	Acceptor::getSocket()
  {
    return (_asocket);
  }

  TcpSocket* Acceptor::getAcceptSocket()
  {
    return (_usocket);
  }

  void Acceptor::acceptSocket()
  {
    SOCKET	usocket;
    SOCKADDR_IN	usin = { 0 };
    unsigned int	sinsize = sizeof usin;

    usocket = accept(_asocket, (SOCKADDR *)&usin, &sinsize);
    if(usocket == INVALID_SOCKET)
      throw NetworkException("Acceptor accept failed");
    _usocket = new TcpSocket(usocket, usin);
  }

  void Acceptor::setObserver(AcceptorObserver * observer)
  {
    _observer = observer;
  }

  void Acceptor::notifyAccept()
  {
    _observer->onAccept(this);
  }

} /* namespace Network */
