#ifndef UDP_SOCKET_HH
# define UDP_SOCKET_HH

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

# include <iostream>
# include <string>

namespace Network
{

  class UdpSocketObserver;

  class UdpSocket
  {
  public:
    UdpSocket();
    ~UdpSocket();

    SOCKET		getSocket();
    void		sendDataTo(const void *data, int size, unsigned int port, const std::string & host);
    int			recvDataFrom(void *data, int size, unsigned int & port, std::string & host);
    void		bindSocket(unsigned int port);

    void		setObserver(UdpSocketObserver * observer);
    void		notifyRead();
    void		notifyWrite();

  private:
    UdpSocketObserver *	_observer;
    SOCKET		_socket;
  };

} /* namespace Network */

#endif /* UDP_SOCKET_HH */
