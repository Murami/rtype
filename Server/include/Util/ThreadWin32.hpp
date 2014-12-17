#ifndef UTIL_THREAD
#define UTIL_THREAD

#include <windows.h>

namespace Util
{
  template<class T>
  DWORD __stdcall launch_thread(LPVOID param);

  template<>
  DWORD __stdcall launch_thread<void>(LPVOID param);

  template<class T>
  class Thread
  {
  private:
    T			_param;
    HANDLE		_thread;

  public:
    Thread()
    {
      _thread = NULL;
    }

    Thread(T param)
    {
      _thread = NULL;
      _param = param;
    }

    ~Thread()
    {
      if (_thread)
	this->join();
    }

    void				start()
    {
      if (_thread == NULL)
	_thread = CreateThread(NULL, 0, launch_thread<T>, this, 0, NULL);
    }

    void				cancel()
    {
      if (_thread)
	TerminateThread(_thread, 0);
      CloseHandle(_thread);
      _thread = NULL;
    }

    void				join()
    {
      WaitForSingleObject(_thread, INFINITE);
      CloseHandle(_thread);
      _thread = NULL;
    }

    void				setParam(const T& param)
    {
      _param = param;
    }

    const T&			getParam() const
    {
      return (_param);
    }

    virtual int run(T parameter) = 0;
  };

  template<>
  class Thread<void>
  {
  private:
    HANDLE		_thread;

  public:
    Thread()
    {
      _thread = NULL;
    }

    ~Thread()
    {
      if (_thread)
	this->join();
    }

    void				start()
    {
      if (_thread == NULL)
	_thread = CreateThread(NULL, 0, launch_thread<void>, this, 0, NULL);
    }

    void				cancel()
    {
      if (_thread)
	TerminateThread(_thread, 0);
      _thread = NULL;
    }

    void				join()
    {
      WaitForSingleObject(_thread, INFINITE);
      CloseHandle(_thread);
      _thread = NULL;
    }

    virtual int run() = 0;
  };

  template<class T>
  DWORD __stdcall launch_thread(LPVOID param)
  {
    Thread<T>* thread = reinterpret_cast<Thread<T>*>(param);
    return (thread->run(thread->getParam()));
  }
};

#endif /* UTIL_THREAD */
