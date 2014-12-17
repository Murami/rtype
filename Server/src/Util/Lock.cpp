#include "Util/Lock.hh"

namespace Util
{
  Lock::Lock(Util::Mutex& mutex) :
    _mutex(mutex)
  {
    _mutex.lock();
  }

  Lock::~Lock()
  {
    _mutex.unlock();
  }
};
