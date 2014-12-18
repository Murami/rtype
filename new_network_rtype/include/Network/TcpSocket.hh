#ifndef TCP_SOCKET_HH
# define TCP_SOCKET_HH

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

# include <iostream>
# include <string>
# include "Buffer.hh"

namespace Network
{

  class TcpSocketObserver;

  class TcpSocket
  {
  public:
    TcpSocket(unsigned int port, const std::string & host);
    TcpSocket(SOCKET socket, SOCKADDR_IN usin);
    ~TcpSocket();

    SOCKET		getSocket();
    void		sendData(const void *data, int size);
    void		readData(void *data, int size);
    void		pickData(void *data, int size);
    void		consumeData(int size);
    void		writeData();
    int			availableDataOnRead();
    int			availableDataOnWrite();

    void		setObserver(TcpSocketObserver *);
    void		notifyRead();
    void		notifyWrite();

  private:
    TcpSocketObserver *	_observer;
    SOCKET		_socket;
    SOCKADDR_IN		_usin;
    Util::Buffer	_readbuf;
    Util::Buffer	_writebuf;
  };

} /* namespace Network */

#endif /* TCP_SOCKET_HH */
