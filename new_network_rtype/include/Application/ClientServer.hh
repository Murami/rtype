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
    ClientServer(Server & server, Network::TcpSocket & socket);
    ~ClientServer();

    void	onRead(Network::TcpSocket & socket);
    void	onWrite(Network::TcpSocket & socket);

    void	notify(int const & type, const Network::Magic *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::User *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::Message *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::RoomConnection *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::PingPong *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::Score *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::MapChange *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::GameReadyState *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::EndGame *, Network::TcpSocket *) const ;
    void	notify(int const & type, const Network::Room *, Network::TcpSocket *) const ;
    void	notify(int const & type, Network::TcpSocket *) const ;

    // void			setRoom(Room * room);

  private:
    Server &			_server;
    Network::TcpSocket &	_socket;
    // Room *			_room;
  };

} /* namespace Application */

#endif /* CLIENT_SERVER_HH */
