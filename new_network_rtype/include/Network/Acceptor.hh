#ifndef ACCEPTOR_HH
# define ACCEPTOR_HH

# ifdef _WIN32

#	include <winsock2.h>

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

# include <string>

namespace Network
{
  class AcceptorObserver;
  class TcpSocket;
  class Acceptor
  {
  public:
    Acceptor(unsigned int port);
    ~Acceptor();

    SOCKET		getSocket();
    TcpSocket*		getAcceptSocket();
    void		acceptSocket();
    void		setObserver(AcceptorObserver *);
    void		notifyAccept();

  private:
    AcceptorObserver*	_observer;
    SOCKET		_asocket;
    TcpSocket*		_usocket;
  };

} /* namespace Network */

#endif /* ACCEPTOR_HH */
