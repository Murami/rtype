#include "Buffer.hh"

#include <iostream>

namespace Util
{

  Buffer::Buffer() {}

  Buffer::~Buffer() {}

  void  Buffer::read(char *buffer, int size)
  {
    for (int i = 0; i < size; ++i)
      {
	buffer[i] = _buffer.front();
	_buffer.pop_front();
      }
  }

  void  Buffer::write(const char *buffer, int size)
  {
    for (int i = 0; i < size; ++i)
      _buffer.push_back(buffer[i]);
  }

  void	Buffer::pick(char *buffer, int size)
  {
    std::deque<char>::iterator it;
    int i;

    for (i = 0, it = _buffer.begin(); i < size && it != _buffer.end(); ++it, ++i)
      buffer[i] = *it;
  }

  void	Buffer::consume(int size)
  {
    for (int i = 0; i < size; ++i)
      _buffer.pop_front();
  }

  int   Buffer::size()
  {
    return (_buffer.size());
  }

} /* namespace Util */
