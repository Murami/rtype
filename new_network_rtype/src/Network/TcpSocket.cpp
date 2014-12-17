#include <cstring>
#include "TcpSocket.hh"
#include "TcpSocketObserver.hh"
#include "NetworkException.hh"

namespace Network
{

  TcpSocket::TcpSocket(unsigned int port, const std::string & host)
  {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket == INVALID_SOCKET)
      throw NetworkException("tcp socket initialization failed");

    memset(&_usin, 0, sizeof(_usin));
    _usin.sin_addr.s_addr = inet_addr(host.c_str());
    _usin.sin_port = htons(port);
    _usin.sin_family = AF_INET;

    if(connect(_socket,(SOCKADDR *) &_usin, sizeof(SOCKADDR)) == SOCKET_ERROR)
      throw NetworkException("tcp connect failed");
  }

  TcpSocket::TcpSocket(SOCKET socket, SOCKADDR_IN usin) : _socket(socket), _usin(usin) {}

  TcpSocket::~TcpSocket()
  {
    closesocket(_socket);
  }

  SOCKET	TcpSocket::getSocket()
  {
    return (_socket);
  }

  void TcpSocket::sendData(const void *data, int size)
  {
    _writebuf.write((const char*)data, size);
  }

  void TcpSocket::readData(void *data, int size)
  {
    _readbuf.read((char*)data, size);
  }

  void TcpSocket::pickData(void *data, int size)
  {
    _readbuf.pick((char*)data, size);
  }

  void TcpSocket::consumeData(int size)
  {
    _readbuf.consume(size);
  }

  void TcpSocket::writeData()
  {
    int size = _writebuf.size();
    char* buffer = new char[size];
    _writebuf.read(buffer, size);

    if(send(_socket, (const char*)buffer, size, 0) < 0)
      throw NetworkException("tcp send data failed");
  }

  int TcpSocket::availableDataOnRead()
  {
    return (_readbuf.size());
  }

  int TcpSocket::availableDataOnWrite()
  {
    return (_writebuf.size());
  }

  void TcpSocket::notifyRead()
  {
    char	buffer[4096];
    int	n;

    if((n = recv(_socket, buffer, 4096, 0)) <= 0)
      throw NetworkException("tcp read failed");
    _readbuf.write(buffer, n);
    _observer->onRead(*this);
  }

  void TcpSocket::notifyWrite()
  {
    _observer->onWrite(*this);
  }

  void TcpSocket::setObserver(TcpSocketObserver * observer)
  {
    _observer = observer;
  }

} /* namespace network */
