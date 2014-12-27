#ifndef SERVER_HH
# define SERVER_HH

#include "Service.hh"
#include "Acceptor.hh"
#include "AcceptorObserver.hh"
#include "UdpSocket.hh"
#include "UdpSocketObserver.hh"
#include "Timer.hh"
#include "TimerObserver.hh"
#include "ClientServer.hh"
#include "Protocole.hh"
#include "Room.hh"
#include "ProtocoleObserver.hh"
#include "EndPoint.hh"

namespace Application
{
  class Server : public Network::AcceptorObserver,
		 public Network::UdpSocketObserver,
		 public Network::TimerObserver,
		 public Network::IUdpProtocoleObserver
  {
  public:
    Server(Network::Service & service);
    ~Server();

    void				run();

    // Protocol notifications
    void	notify(int const& type, const RtypeProtocol::State* state, const unsigned int & port, const std::string& host);
    void	notify(int const& type, const RtypeProtocol::EntityRequest* request, const unsigned int & port, const std::string& host);

    // Network events
    void	onAccept(Network::Acceptor & socket);
    void	onRead(Network::UdpSocket & socket);
    void	onWrite(Network::UdpSocket & socket);
    void	onTimeout(Network::Timer & timer);

    // Getters
    Network::Service &			getService() const;
    const Network::ProtocoleTcp &	getProtocole() const;
    const Network::ProtocoleUdp&	getProtocoleUdp() const;

    // ClientServer
    void	deleteClientServer(ClientServer * client);

    // Send functions
    void	sendAllRoomInfos(ClientServer* server) const;
    void	sendRoomToAllClients(const Room* room, bool alive);
    void	sendUdp(const ClientServer& client, const void* data, size_t size);

    // Room
    Room*	createRoom(ClientServer* client, const RtypeProtocol::Room* room);
    Room*	getRoom(unsigned int roomID) const;
    bool	roomExists(const std::string& name) const;
    void	deleteRoom(Room* room);

    // ClientRoom
    void	addClientRoom(ClientRoom* clientroom);
    void	deleteClientRoom(ClientRoom* clientroom);
    bool	isValidEndpoint(const std::string& host, unsigned short port) const;

  private:
    // Protocole attribute
    Network::ProtocoleUdp	_protocoleUdp;
    Network::ProtocoleTcp	_protocoleTcp;

    // Network attributes
    Network::Service&	_service;
    Network::Timer	_timer1;
    Network::Acceptor	_acceptor;
    Network::UdpSocket	_udpSocket;

    // Server attribute
    std::list<ClientServer*>			_clients;
    std::map<Network::EndPoint, ClientRoom*>	_clientsroom;
    std::map<unsigned int, Room*>		_rooms;
  };

} /* namespace Application */

#endif /* SERVER_HH */
