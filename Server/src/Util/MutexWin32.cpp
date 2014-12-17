#include "Util/Mutex.hh"

namespace Util
{
  Mutex::Mutex()
  {
    InitializeCriticalSection(&_section);
  }

  Mutex::~Mutex()
  {
    DeleteCriticalSection(&_section);
  }

  void	Mutex::lock()
  {
    EnterCriticalSection(&_section);
  }

  bool	Mutex::trylock()
  {
    return (TryEnterCriticalSection(&_section));
  }

  void	Mutex::unlock()
  {
    LeaveCriticalSection(&_section);
  }
};
