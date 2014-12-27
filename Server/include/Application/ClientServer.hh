#ifndef CLIENT_SERVER_HH
# define CLIENT_SERVER_HH

#include "TcpSocket.hh"
#include "TcpSocketObserver.hh"
#include "ProtocoleObserver.hh"
#include "Room.hh"

#define send(sock, data)		(sock.sendData(&data, sizeof(data)))

namespace Application
{
  class Server;

  class ClientServer : public Network::TcpSocketObserver,
		       public Network::ITcpProtocoleObserver,
		       public Network::TimerObserver
  {
  public:
    enum State
      {
	T_MAGIC_WAITING,
	T_DISCONNECTED,
	T_CONNECTED,
	T_INROOM,
	T_INGAME
      };

  public:
    ClientServer(Server & server, Network::TcpSocket & socket);
    ~ClientServer();

    // Network notifications
    void	onRead(Network::TcpSocket & socket, const bool error = false);
    void	onWrite(Network::TcpSocket & socket);
    void	onTimeout(Network::Timer& timer);

    // Protocol notifications
    void	notify(int const & type, const RtypeProtocol::Magic *,
		       Network::TcpSocket *);
    void	notify(int const & type, const RtypeProtocol::User *,
		       Network::TcpSocket *);
    void	notify(int const & type, const RtypeProtocol::Message *,
		       Network::TcpSocket *);
    void	notify(int const & type, const RtypeProtocol::RoomConnection *,
		       Network::TcpSocket *);
    void	notify(int const & type, const RtypeProtocol::PingPong *,
		       Network::TcpSocket *);
    void	notify(int const & type, const RtypeProtocol::Room *,
		       Network::TcpSocket *);
    void	notify(int const & type, Network::TcpSocket *) ;

    // Getters
    Network::TcpSocket& getSocket() const;
    ClientRoom*		getClientRoom() const;
    const std::string&	getName() const;
    Server&		getServer() const;
    State		getState() const;
    const std::string&	getIP() const;
    unsigned short	getPort() const;

    // Setters
    void	setClientRoom(ClientRoom* clientroom);

    // Senders
    void	sendHeader(int type, unsigned int size = 0);
    void	sendRoomInfos(const Room* room, bool alive);
    void	sendUdp(const void* data, size_t size);

  private:
    Server&			_server;
    Network::TcpSocket&		_socket;
    State			_state;
    ClientRoom*			_clientroom;
    std::string			_name;
    Network::Timer		_timer;
    unsigned short		_udpport;
  };

} /* namespace Application */

#endif /* CLIENT_SERVER_HH */
