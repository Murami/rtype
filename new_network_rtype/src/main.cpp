#include <iostream>
#include "Service.hh"
#include "Server.hh"

#include "RtypeProtocol.hh"
#include <cstddef>
#include <iostream>
#include "NetworkException.hh"

int main()
{
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
