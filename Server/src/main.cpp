#include <iostream>
#include "Service.hh"
#include "Server.hh"

#include "RtypeProtocol.hh"
#include <iostream>
#include <ctime>
#include "NetworkException.hh"

int main()
{
  std::srand(std::time(NULL));
  try
  {
    Network::Service	service;
    Application::Server	server(service);

    server.run();
  }
  catch (const Network::NetworkException &e)
  {
    std::cerr << "Unable to start the server + " << e.what() << std::endl;
  }
  return (0);
}
