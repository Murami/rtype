#ifndef PROTOCOLEOBSERVER_HH_
# define PROTOCOLEOBSERVER_HH_

# include "TcpSocket.hh"
# include "UdpSocket.hh"
# include "RtypeProtocol.hh"

namespace Network
{
  class ITcpProtocoleObserver
  {
  public:
    ~ITcpProtocoleObserver()
    {}
    virtual void	notify(int const &type, const RtypeProtocol::Magic *, TcpSocket *) = 0;
    virtual void	notify(int const &type, const RtypeProtocol::User *, TcpSocket *) = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Message *, TcpSocket *) = 0;
    virtual void	notify(int const &type, const RtypeProtocol::RoomConnection *, TcpSocket *) = 0;
    virtual void	notify(int const &type, const RtypeProtocol::PingPong *, TcpSocket *) = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Room *, TcpSocket *) = 0;
    virtual void	notify(int const &type, TcpSocket *) = 0;
  };

  class IUdpProtocoleObserver
  {
  public:
    ~IUdpProtocoleObserver()
    {}
    virtual void	notify(int const &type, const RtypeProtocol::PositionEvent *, UdpSocket *) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Spawn *, UdpSocket *) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Position *, UdpSocket *) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::destruction *, UdpSocket *) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Life *, UdpSocket *) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Bonus *, UdpSocket *) const = 0;
    virtual void	notify(int const &type, UdpSocket *) const = 0;
  };
}

#endif // !PROTOCOLEOBSERVER_HH_
