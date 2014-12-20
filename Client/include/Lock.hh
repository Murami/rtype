#ifndef UTIL_LOCK
#define UTIL_LOCK

#include "Mutex.hh"

namespace Util
{
  class Lock
  {
    Util::Mutex& _mutex;

  public:
    Lock(Util::Mutex& mutex);
    ~Lock();
  };
};

#endif /* UTIL_LOCK */