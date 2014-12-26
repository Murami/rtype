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

    void	notify(int const & type, const RtypeProtocol::State* state, const unsigned int & port, const std::string& host);
    void	notify(int const & type, const RtypeProtocol::EntityRequest* request, const unsigned int & port, const std::string& host);

    // Network events
    void				onAccept(Network::Acceptor & socket);
    void				onRead(Network::UdpSocket & socket);
    void				onWrite(Network::UdpSocket & socket);
    void				onTimeout(Network::Timer & timer);

    // Get composite objects
    Network::Service &			getService() const;
    const Network::ProtocoleTcp &	getProtocole() const;

    // ClientServer
    void				deleteClientServer(ClientServer * client);

    // Room
    Room*				createRoom(ClientServer* client, const RtypeProtocol::Room* room);
    Room*				getRoom(unsigned int roomID) const;
    void				addClientRoom(ClientRoom* clientroom);
    void				deleteClientRoom(ClientRoom* clientroom);
    bool				roomExists(const std::string& name) const;
    void				sendAllRoomInfos(ClientServer* server) const;
    void				sendRoomToAllClients(const Room* room, bool alive);
    void				deleteRoom(Room* room);
    bool				isValidIp(std::string ip);
    void				addClientPort(std::string ip, unsigned int port);

  private:
    Network::Service &			_service;
    Network::ProtocoleUdp		_protocoleUdp;
    Network::ProtocoleTcp		_protocoleTcp;

    Network::Acceptor			_acceptor;
    Network::UdpSocket			_udpSocket;

    std::list<ClientServer*>		_clients;
    std::map<std::string, ClientRoom*>	_clientsroom;
    std::map<unsigned int, Room*>	_rooms;
    std::map<std::string, unsigned int> _ports;

    Network::Timer			_timer1;
  };

} /* namespace Application */

#endif /* SERVER_HH */
