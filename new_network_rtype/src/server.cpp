#include <iostream>
#include "Service.hh"
#include "Acceptor.hh"
#include "TcpSocket.hh"
#include "UdpSocket.hh"
#include "Timer.hh"
#include "AcceptorObserver.hh"
#include "TcpSocketObserver.hh"
#include "UdpSocketObserver.hh"
#include "TimerObserver.hh"

int main()
{
  Network::Service	service;
  Application::Server	server(service);

  server.run();
  return (0);
}
