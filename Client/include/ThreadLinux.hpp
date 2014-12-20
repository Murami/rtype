#ifndef UTIL_THREAD
#define UTIL_THREAD

#include <pthread.h>

namespace Util
{
  template<class T>
  void* launch_thread(void* param);

  template<>
  void* launch_thread<void>(void* param);

  template<class T>
  class Thread
  {
  private:
    T			_param;
    pthread_t		_thread;
    bool		_started;

  public:
    Thread()
    {
      _started = false;
    }

    Thread(T param)
    {
      _started = false;
      _param = param;
    }

    ~Thread()
    {
      if (_started)
	this->join();
    }

    void		start()
    {
      if (!_started)
	{
	  pthread_create(&_thread, NULL,  launch_thread<T>, this);
	  _started = true;
	}
    }

    void		cancel()
    {
      if (_started)
	{
	  pthread_cancel(_thread);
	  _started = false;
	}
    }

    void		join()
    {
      if (_started)
	{
	  pthread_join(_thread, NULL);
	  pthread_detach(_thread);
	  _started = false;
	}
    }

    void		setParam(const T& param)
    {
      _param = param;
    }

    const T&		getParam() const
    {
      return (_param);
    }

    virtual int run(T parameter) = 0;
  };

  template<>
  class Thread<void>
  {
  private:
    pthread_t		_thread;
    bool		_started;

  public:
    Thread();
    ~Thread();
    void		start();
    void		cancel();
    void		join();

    virtual int		run() = 0;
  };

  template<class T>
  void* launch_thread(void* param)
  {
    Thread<T>* thread = reinterpret_cast<Thread<T>*>(param);
    thread->run(thread->getParam());
    return (NULL);
  }
};

#endif /* UTIL_THREAD */
