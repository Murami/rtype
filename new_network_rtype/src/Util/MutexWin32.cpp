#ifdef _WIN32
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
	  if (TryEnterCriticalSection(&_section))
		  return (true);
	  return (false);
  }

  void	Mutex::unlock()
  {
    LeaveCriticalSection(&_section);
  }
};
#endif
