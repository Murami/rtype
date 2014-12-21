#include <iostream>
#include "Service.hh"
#include "Server.hh"

#include "RtypeProtocol.hh"
#include <iostream>

int main()
{
	/*
	RtypeProtocol::Room	room;
	std::cout << "id : " << offsetof(RtypeProtocol::Room, id) << std::endl;
	std::cout << "alive : " << offsetof(RtypeProtocol::Room, alive) << std::endl;
	std::cout << "connected_user : " << offsetof(RtypeProtocol::Room, connected_users) << std::endl;
	std::cout << "nb_connected_users : " << offsetof(RtypeProtocol::Room, nb_connected_users) << std::endl;
	std::cout << "ipassword_flagd : " << offsetof(RtypeProtocol::Room, password_flag) << std::endl;
	std::cout << "pass_md5 : " << offsetof(RtypeProtocol::Room, pass_md5) << std::endl;
	std::cout << "room_name : " << offsetof(RtypeProtocol::Room, room_name) << std::endl;
	std::cout << "ready_users : " << offsetof(RtypeProtocol::Room, ready_users) << std::endl;
	std::cout << "locked : " << offsetof(RtypeProtocol::Room, locked) << std::endl;
	std::cout << "users_id : " << offsetof(RtypeProtocol::Room, users_id) << std::endl;
	*/
  Network::Service	service;
  Application::Server	server(service);

  server.run();
  return (0);
}
