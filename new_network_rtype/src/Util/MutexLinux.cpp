#ifdef __linux__
#include "Util/Mutex.hh"

namespace Util
{
  Mutex::Mutex()
  {
    pthread_mutex_init(&_mutex, NULL);
  }

  Mutex::~Mutex()
  {
    pthread_mutex_destroy(&_mutex);
  }

  void	Mutex::lock()
  {
    pthread_mutex_lock(&_mutex);
  }

  bool	Mutex::trylock()
  {
    if (pthread_mutex_trylock(&_mutex) == 0)
      return (true);
    return (false);
  }

  void	Mutex::unlock()
  {
    pthread_mutex_unlock(&_mutex);
  }
};
#endif
