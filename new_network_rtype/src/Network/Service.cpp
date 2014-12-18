#include "Service.hh"
#include "Timer.hh"
#include "TcpSocket.hh"
#include "UdpSocket.hh"
#include "Acceptor.hh"
#include "NetworkException.hh"

#include <iostream>

namespace Network
{

  Service::TimerRAII::TimerRAII(Timer* timer) : _timer(timer) {}

  Service::TimerRAII::TimerRAII(const Service::TimerRAII& timerRAII)
  {
    _timer = timerRAII._timer;
  }

  Service::TimerRAII&	Service::TimerRAII::operator=(const Service::TimerRAII& timerRAII)
  {
    this->_timer = timerRAII._timer;
    return (*this);
  }

  bool Service::TimerRAII::operator==(const Service::TimerRAII& timer) const
  {
    return (_timer->getTime() == timer->getTime());
  }

  bool Service::TimerRAII::operator!=(const Service::TimerRAII& timer) const
  {
    return (_timer->getTime() != timer->getTime());
  }

  bool Service::TimerRAII::operator<=(const Service::TimerRAII& timer) const
  {
    return (_timer->getTime() <= timer->getTime());
  }

  bool Service::TimerRAII::operator>=(const Service::TimerRAII& timer) const
  {
    return (_timer->getTime() >= timer->getTime());
  }

  bool Service::TimerRAII::operator<(const Service::TimerRAII& timer) const
  {
    return (_timer->getTime() < timer->getTime());
  }

  bool Service::TimerRAII::operator>(const Service::TimerRAII& timer) const
  {
    return (_timer->getTime() > timer->getTime());
  }

  Timer* Service::TimerRAII::operator->() const
  {
    return (_timer);
  }

  Timer* Service::TimerRAII::operator*() const
  {
    return (_timer);
  }

  Service::Service()
  {
	#ifdef WIN32

	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if(err < 0)
	  throw NetworkException("WSAStartup failed");

	#endif
  }

  Service::~Service()
  {
	#ifdef WIN32

	WSACleanup();

	#endif
  }

  void Service::run()
  {
    int			fd = 0;
    int			ret = 0;
    fd_set		readfs;
    fd_set		writefs;
    struct timeval	tv;

    while (_Timers.size() || _RSocketUdp.size() || _RSocketTcp.size() ||
	   _WSocketUdp.size() || _WSocketTcp.size() || _Acceptors.size())
      {
	std::chrono::system_clock::duration	now = std::chrono::system_clock::now().time_since_epoch();

	// Initalize sets
	FD_ZERO(&readfs);
	FD_ZERO(&writefs);
	ret = setRead(&readfs);
	fd = (ret > fd) ? ret : fd;
	ret = setWrite(&writefs);
	fd = (ret > fd) ? ret : fd;

	// Run through list of timer to determine the expireds ones and run them
	while (_Timers.size() && _Timers.front()->getTime() <= now)
	  {
	    Service::TimerRAII	tmp = _Timers.front();

	    _Timers.pop_front();
	    tmp->notify();
	  }

	// Send informations to select with timer information
	if (_Timers.size())
	  {
	    std::chrono::system_clock::duration	waittime = _Timers.front()->getTime() - now;
	    duration_second			sec;
	    duration_microsecond		usec;

	    sec = std::chrono::duration_cast<duration_second>(waittime);
	    usec = std::chrono::duration_cast<duration_microsecond>(waittime) - sec;

	    tv.tv_sec = sec.count();
	    tv.tv_usec = usec.count();
	    std::cout << tv.tv_sec << " - " << tv.tv_usec << std::endl;
	    if ((ret = select(fd + 1, &readfs, &writefs, NULL, &tv)) < 0)
	      throw NetworkException("Service select failed");
	    if (ret == 0)
	      {
		Service::TimerRAII	tmp = _Timers.front();

		_Timers.pop_front();
		tmp->notify();
	      }
	  }
	// Send informations to select without timer information
	else
	  if ((ret = select(fd + 1, &readfs, &writefs, NULL, NULL)) < 0)
	    throw NetworkException("Service select failed");

	notifyRTcp(&readfs);
	notifyWTcp(&writefs);
	notifyRUdp(&readfs);
	notifyWUdp(&writefs);
	notifyAcceptor(&readfs);
      }
  }

  int  Service::setRead(fd_set* readfs)
  {
    int fd = 0;
    std::map<SOCKET, TcpSocket *>::iterator tcpIt;
    std::map<SOCKET, UdpSocket *>::iterator udpIt;
    std::map<SOCKET,Acceptor *>::iterator  accIt;

    for (tcpIt = _RSocketTcp.begin(); tcpIt != _RSocketTcp.end(); ++tcpIt)
      {
	FD_SET(tcpIt->first, readfs);
	fd = (tcpIt->first > fd) ? tcpIt->first : fd;
      }

    for (udpIt = _RSocketUdp.begin(); udpIt != _RSocketUdp.end(); ++udpIt)
      {
	FD_SET(udpIt->first, readfs);
	fd = (udpIt->first > fd) ? udpIt->first : fd;
      }

    for (accIt = _Acceptors.begin(); accIt != _Acceptors.end(); ++accIt)
      {
	FD_SET(accIt->first, readfs);
	fd = (accIt->first > fd) ? accIt->first : fd;
      }
    return fd;
  }

  int  Service::setWrite(fd_set* writefs)
  {
    int fd = 0;
    std::map<SOCKET, TcpSocket *>::iterator tcpIt;
    std::map<SOCKET, UdpSocket *>::iterator udpIt;

    for (tcpIt = _WSocketTcp.begin(); tcpIt != _WSocketTcp.end(); ++tcpIt)
      {
	if (tcpIt->second->availableDataOnWrite() > 0)
	  {
	    FD_SET(tcpIt->first, writefs);
	    fd = (tcpIt->first > fd) ? tcpIt->first : fd;
	  }
      }

    for (udpIt = _WSocketUdp.begin(); udpIt != _WSocketUdp.end(); ++udpIt)
      {
	FD_SET(udpIt->first, writefs);
	fd = (udpIt->first > fd) ? udpIt->first : fd;
      }
    return fd;
  }

  void Service::notifyRTcp(fd_set * readfs)
  {
    std::list<TcpSocket*>				del;
    std::list<TcpSocket*>::iterator		delIt;
    std::map<SOCKET, TcpSocket *>::iterator	RTcpIt;

    for (RTcpIt = _RSocketTcp.begin(); RTcpIt != _RSocketTcp.end(); ++RTcpIt)
      if (FD_ISSET(RTcpIt->first, readfs))
	del.push_front(RTcpIt->second);
    for (delIt = del.begin(); delIt != del.end(); ++delIt)
      {
	_RSocketTcp.erase((*delIt)->getSocket());
	(*delIt)->notifyRead();
      }
    del.clear();
  }

  void Service::notifyWTcp(fd_set * writefs)
  {
    std::list<TcpSocket*>			del;
    std::list<TcpSocket*>::iterator		delIt;
    std::map<SOCKET, TcpSocket *>::iterator	WTcpIt;

    for (WTcpIt = _WSocketTcp.begin(); WTcpIt != _WSocketTcp.end(); ++WTcpIt)
      if (FD_ISSET(WTcpIt->first, writefs))
	{
	  WTcpIt->second->writeData();
	  del.push_front(WTcpIt->second);
	}
    for (delIt = del.begin(); delIt != del.end(); ++delIt)
      {
	_WSocketTcp.erase((*delIt)->getSocket());
	(*delIt)->notifyWrite();
      }
    del.clear();
  }

  void Service::notifyRUdp(fd_set * readfs)
  {
    std::list<UdpSocket*>				del;
    std::list<UdpSocket*>::iterator		delIt;
    std::map<SOCKET, UdpSocket *>::iterator	RUdpIt;

    for (RUdpIt = _RSocketUdp.begin(); RUdpIt != _RSocketUdp.end(); ++RUdpIt)
      if (FD_ISSET(RUdpIt->first, readfs))
	del.push_front(RUdpIt->second);
    for (delIt = del.begin(); delIt != del.end(); ++delIt)
      {
	_RSocketUdp.erase((*delIt)->getSocket());
	(*delIt)->notifyRead();
      }
    del.clear();
  }

  void Service::notifyWUdp(fd_set * writefs)
  {
    std::list<UdpSocket*>				del;
    std::list<UdpSocket*>::iterator		delIt;
    std::map<SOCKET, UdpSocket *>::iterator	WUdpIt;

    for (WUdpIt = _WSocketUdp.begin(); WUdpIt != _WSocketUdp.end(); ++WUdpIt)
      if (FD_ISSET(WUdpIt->first, writefs))
	del.push_front(WUdpIt->second);
    for (delIt = del.begin(); delIt != del.end(); ++delIt)
      {
	_WSocketUdp.erase((*delIt)->getSocket());
	(*delIt)->notifyWrite();
      }
    del.clear();
  }

  void Service::notifyAcceptor(fd_set * readfs)
  {
    std::list<Acceptor*>				del;
    std::list<Acceptor*>::iterator		delIt;
    std::map<SOCKET, Acceptor *>::iterator	AccIt;

    for (AccIt = _Acceptors.begin(); AccIt != _Acceptors.end(); ++AccIt)
      if (FD_ISSET(AccIt->first, readfs))
	del.push_front(AccIt->second);
    for (delIt = del.begin(); delIt != del.end(); ++delIt)
      {
	_Acceptors.erase((*delIt)->getSocket());
	(*delIt)->notifyAccept();
      }
    del.clear();
  }

  void Service::addTimeout(Timer & timer)
  {
    std::list<TimerRAII>::iterator it;

    it = _Timers.begin();
    while (it != _Timers.end())
      {
	if (*(*it) == &timer)
	  it = _Timers.erase(it);
	else
	  ++it;
      }

    for (it = _Timers.begin(); it != _Timers.end(); it++)
      if ((*(*it))->getTime() > timer.getTime())
	{
	  _Timers.insert(it, TimerRAII(&timer));
	  return;
	}
    _Timers.insert(it, TimerRAII(&timer));
  }

  void Service::addReadTcp(TcpSocket & socket)
  {
    _RSocketTcp.insert(std::pair<SOCKET, TcpSocket*>(socket.getSocket(), &socket));
  }

  void Service::addWriteTcp(TcpSocket & socket)
  {
    _WSocketTcp.insert(std::pair<SOCKET, TcpSocket*>(socket.getSocket(), &socket));
  }

  void Service::addReadUdp(UdpSocket & socket)
  {
    _RSocketUdp.insert(std::pair<SOCKET, UdpSocket*>(socket.getSocket(), &socket));
  }

  void Service::addWriteUdp(UdpSocket & socket)
  {
    _WSocketUdp.insert(std::pair<SOCKET, UdpSocket*>(socket.getSocket(), &socket));
  }

  void Service::addAcceptor(Acceptor & socket)
  {
    _Acceptors.insert(std::pair<SOCKET, Acceptor*>(socket.getSocket(), &socket));
  }

} /* namespace Network */
