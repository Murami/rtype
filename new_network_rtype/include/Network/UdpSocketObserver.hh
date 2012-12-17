#ifndef UDP_SOCKET_OBSERVER_HH
# define UDP_SOCKET_OBSERVER_HH

namespace Network
{

  class UdpSocket;

  class UdpSocketObserver
  {
  public:
    virtual void onRead(UdpSocket*) = 0;
    virtual void onWrite(UdpSocket*) = 0;
  };

} /* namespace Network */

#endif /* UDP_SOCKET_OBSERVER_HH */
