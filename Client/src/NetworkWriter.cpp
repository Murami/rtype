#include	<iostream>
#include	"NetworkWriter.hh"
#include	"Mutex.hh"
#include	"Lock.hh"
#include	"TcpConnection.hh"

NetworkWriter::NetworkWriter(TcpConnection& connection) :
  _tcpConnection(connection)
{
  _cond.lock();
}

NetworkWriter::~NetworkWriter() {}

int		NetworkWriter::run()
{
  char		buffer[4096];
  std::size_t	i;

  while (1)
    {
      Util::Lock lock(_mutex);
      _cond.lock();
      for (i = 0; i < _buffer.size(); i++)
	{
	  buffer[i] = _buffer.front();
	  _buffer.pop_front();
	}
      if (!_buffer.empty())
	_cond.unlock();
      _tcpConnection.write(buffer, i);
    }
  return (0);
}

void		NetworkWriter::sendData(void *data, std::size_t size)
{
  Util::Lock	lock(_mutex);
  bool		empty;

  empty = _buffer.empty();
  for (std::size_t i = 0; i < size; i++)
    _buffer.push_back(static_cast<char *>(data)[i]);
  if (empty)
    _cond.unlock();
}
