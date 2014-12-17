#ifndef TCP_SOCKET_OBSERVER_HH
# define TCP_SOCKET_OBSERVER_HH

namespace Network
{

  class TcpSocket;

  class TcpSocketObserver
  {
  public:
    virtual void onRead(TcpSocket &) = 0;
    virtual void onWrite(TcpSocket &) = 0;
  };

} /* namespace Network */

#endif /* TCP_SOCKET_OBSERVER_HH */
