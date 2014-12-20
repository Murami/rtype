#include <iostream>
#include "Service.hh"
#include "Server.hh"

int main()
{
  Network::Service	service;
  Application::Server	server(service);

  server.run();
  return (0);
}
