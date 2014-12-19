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

    void	notify(int const & type, const Network::Magic *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::User *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::Message *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::RoomConnection *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::PingPong *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::Score *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::MapChange *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::GameReadyState *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::EndGame *, Network::TcpSocket *) ;
    void	notify(int const & type, const Network::Room *, Network::TcpSocket *) ;
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
