#ifndef CLIENT_SERVER_HH
# define CLIENT_SERVER_HH

#include "TcpSocket.hh"
#include "TcpSocketObserver.hh"
#include "ProtocoleObserver.hh"
// #include "Room.hh"

namespace Application
{
  class Server;

  class ClientServer : public Network::TcpSocketObserver, public Network::ITcpProtocoleObserver
  {
  public:
    enum State
      {
	T_MAGIC_WAITING,
	T_DISCONNECTED,
	T_CONNECTED
      };

  public:
    ClientServer(Server & server, Network::TcpSocket & socket);
    ~ClientServer();

    void	onRead(Network::TcpSocket & socket);
    void	onWrite(Network::TcpSocket & socket);

    void	notify(int const & type, const RtypeProtocol::Magic *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::User *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::Message *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::RoomConnection *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::PingPong *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::Score *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::MapChange *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::GameReadyState *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::EndGame *, Network::TcpSocket *) ;
    void	notify(int const & type, const RtypeProtocol::Room *, Network::TcpSocket *) ;
    void	notify(int const & type, Network::TcpSocket *) ;

    Network::TcpSocket & getSocket() const;

    // void			setRoom(Room * room);

  private:
    Server &			_server;
    Network::TcpSocket &	_socket;
    State			_state;
    // Room *			_room;
  };

} /* namespace Application */

#endif /* CLIENT_SERVER_HH */
