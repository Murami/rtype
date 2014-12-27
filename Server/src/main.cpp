#include <iostream>
#include "Service.hh"
#include "Server.hh"

#include "RtypeProtocol.hh"
#include <cstddef>
#include <iostream>
#include "NetworkException.hh"

int main()
{
  std::cout << "Sizeof State : " << sizeof(RtypeProtocol::State) << std::endl;
  std::cout << "id      " << offsetof (RtypeProtocol::State, id) << std::endl;
  std::cout << "state : " << offsetof (RtypeProtocol::State, state) << std::endl;
      std::cout << "Sizeof EntityRequest : " << sizeof(RtypeProtocol::EntityRequest) << std::endl;
  std::cout << "id " << offsetof (RtypeProtocol::EntityRequest, id) << std::endl;
  try
  {
    Network::Service	service;
    Application::Server	server(service);

    server.run();
  }
  catch (const Network::NetworkException &e)
  {
    std::cout << "Unable to start the server" << std::endl;
  }
  return (0);
}
