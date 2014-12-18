#ifdef __linux__
#include "Util/Thread.hpp"

namespace Util
{
  template<>
  void* launch_thread<void>(void* param)
  {
    Thread<void>* thread = reinterpret_cast<Thread<void>*>(param);
    thread->run();
    return (NULL);
  }
};
#endif
