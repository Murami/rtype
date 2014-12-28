#include	<iostream>
#include	"TcpNetworkWriter.hh"
#include	"Mutex.hh"
#include	"Lock.hh"
#include	"TcpConnection.hh"

TcpNetworkWriter::TcpNetworkWriter(TcpConnection& connection) :
  _tcpConnection(connection)
{
  _cond.lock();
}

TcpNetworkWriter::~TcpNetworkWriter() {}

int		TcpNetworkWriter::run()
{
  char		buffer[4096];
  std::size_t	i;

  while (_tcpConnection.isWriting())
    {
      _cond.lock();
      for (i = 0; i < _buffer.size(); i++)
	{
	  buffer[i] = _buffer.front();
	  _buffer.pop_front();
	}
      if (!_buffer.empty())
	_cond.unlock();

      if (_tcpConnection.socket().send(buffer, i) != sf::Socket::Done)
	{
	  _tcpConnection.exit();
	  return (-1);
	}
    }
  return (0);
}

void		TcpNetworkWriter::sendData(void *data, std::size_t size)
{
  Util::Lock	lock(_mutex);
  bool		empty;

  empty = _buffer.empty();
  for (std::size_t i = 0; i < size; i++)
    _buffer.push_back(static_cast<char *>(data)[i]);
  if (empty)
    _cond.unlock();
}
