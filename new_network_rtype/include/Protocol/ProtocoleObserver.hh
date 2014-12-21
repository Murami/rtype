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
    virtual void  notify(int const &type, const RtypeProtocol::State *, const unsigned int & port, const std::string & host) = 0;
    virtual void  notify(int const &type, const RtypeProtocol::EntityRequest *, const unsigned int & port, const std::string & host) = 0;
    /*
    unused on server side :
    virtual void	notify(int const &type, const RtypeProtocol::PositionEvent *, const unsigned int & port, const std::string & host) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Spawn *, const unsigned int & port, const std::string & host) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Position *, const unsigned int & port, const std::string & host) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::destruction *, const unsigned int & port, const std::string & host) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Life *, const unsigned int & port, const std::string & host) const = 0;
    virtual void	notify(int const &type, const RtypeProtocol::Bonus *, const unsigned int & port, const std::string & host) const = 0;
    virtual void	notify(int const &type, const unsigned int & port, const std::string & host) const = 0;
    */
  };
}

#endif // !PROTOCOLEOBSERVER_HH_
