#if defined(__linux__) || defined(__APPLE__)
# include "Thread.hpp"

namespace Util
{
  template<>
  void* launch_thread<void>(void* param)
  {
    Thread<void>* thread = reinterpret_cast<Thread<void>*>(param);
    thread->run();
    return (NULL);
  }

  Thread<void>::Thread()
  {
    _started = false;
  }

  Thread<void>::~Thread()
  {
    if (_started)
      this->join();
  }

  void		Thread<void>::start()
  {
    if (!_started)
      pthread_create(&_thread, NULL,  launch_thread<void>, this);
  }

  void		Thread<void>::cancel()
  {
    if (_started)
      {
	pthread_cancel(_thread);
	_started = false;
      }
  }

  void		Thread<void>::join()
  {
    if (_started)
      {
	pthread_join(_thread, NULL);
	pthread_detach(_thread);
	_started = false;
      }
  }
};

#endif
