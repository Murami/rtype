#ifndef SERVICE_HH
# define SERVICE_HH

# ifdef _WIN32

#	include <winsock2.h>
  typedef int socklen_t;

# elif defined (__linux__)

	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
	typedef struct in_addr IN_ADDR;

#	include <sys/types.h>
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <arpa/inet.h>
#	include <unistd.h> /* close */
#	include <netdb.h> /* gethostbyname */

#	define INVALID_SOCKET -1
#	define SOCKET_ERROR -1
#	define closesocket(s) close(s)
#	define ioctl(s, cmd, argp) ioctlsocket(s, cmd, argp)

# else

#	error not defined for this platform

# endif /* WIN32 */

# include <map>
# include <list>
# include <vector>
# include <functional>

namespace Network
{

  class Timer;
  class TcpSocket;
  class UdpSocket;
  class Acceptor;

  class Service
  {
  public:
    class TimerRAII
    {
    private:
      Timer*	_timer;

    public:
      TimerRAII(Timer*);
      TimerRAII(const TimerRAII&);
      TimerRAII&	operator=(const TimerRAII&);

      bool	operator==(const TimerRAII& timer) const;
      bool	operator!=(const TimerRAII& timer) const;
      bool	operator<=(const TimerRAII& timer) const;
      bool	operator>=(const TimerRAII& timer) const;
      bool	operator<(const TimerRAII& timer) const;
      bool	operator>(const TimerRAII& timer) const;
      Timer*	operator->() const;
      Timer*	operator*() const;
    };

  public:
    Service();
    ~Service();

    void run();
    void addTimeout(Timer & timer);
    void addReadTcp(TcpSocket & socket);
    void addWriteTcp(TcpSocket & socket);
    void addReadUdp(UdpSocket & socket);
    void addWriteUdp(UdpSocket & socket);
    void addAcceptor(Acceptor & sOBocket);

    void deleteReadTcp(TcpSocket & socket);
    void deleteWriteTcp(TcpSocket & socket);
    void deleteReadUdp(UdpSocket & socket);
    void deleteWriteUdp(UdpSocket & socket);
    void deleteAcceptor(Acceptor & socket);

  private:
    int  setRead(fd_set* readfs);
    int  setWrite(fd_set* writefs);
    void notifyRTcp(fd_set * readfs);
    void notifyWTcp(fd_set * writefs);
    void notifyRUdp(fd_set * readfs);
    void notifyWUdp(fd_set * writefs);
    void notifyAcceptor(fd_set * readfs);

  private:
    std::list<TimerRAII>									_Timers;
    std::map<SOCKET, TcpSocket *>								_RSocketTcp;
    std::map<SOCKET, TcpSocket *>								_WSocketTcp;
    std::map<SOCKET, UdpSocket *>								_RSocketUdp;
    std::map<SOCKET, UdpSocket *>								_WSocketUdp;
    std::map<SOCKET, Acceptor *>								_Acceptors;
  };

} /* namespace Network */

#endif /* SERVICE_HH */
