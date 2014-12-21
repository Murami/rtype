#include <iostream>
#include "Service.hh"
#include "Server.hh"

#include "RtypeProtocol.hh"
#include <iostream>

int main()
{
	RtypeProtocol::Room	room;
	std::cout << "id : " << sizeof(room.id) << std::endl;
	std::cout << "alive : " << sizeof(room.alive) << std::endl;
	std::cout << "connected_user : " << sizeof(room.connected_users) << std::endl;
	std::cout << "nb_connected_users : " << sizeof(room.nb_connected_users) << std::endl;
	std::cout << "ipassword_flagd : " << sizeof(room.password_flag) << std::endl;
	std::cout << "pass_md5 : " << sizeof(room.pass_md5) << std::endl;
	std::cout << "room_name : " << sizeof(room.room_name) << std::endl;
	std::cout << "ready_users : " << sizeof(room.ready_users) << std::endl;
	std::cout << "locked : " << sizeof(room.locked) << std::endl;
	std::cout << "users_id : " << sizeof(room.users_id) << std::endl;
  Network::Service	service;
  Application::Server	server(service);

  server.run();
  return (0);
}
