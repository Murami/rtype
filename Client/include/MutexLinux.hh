#ifndef UTIL_MUTEX
#define UTIL_MUTEX

#include <pthread.h>

namespace Util
{
  class Mutex
  {
  private:
    pthread_mutex_t	_mutex;

  public:
    Mutex();
    ~Mutex();

    void	lock();
    bool	trylock();
    void	unlock();
  };
};

#endif /* UTIL_MUTEX */
