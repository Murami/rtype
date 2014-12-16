#ifndef UTIL_OBSERVER
#define UTIL_OBSERVER

namespace Util
{
  template<class T, class MsgT>
  class Observable;

  template<class T, class MsgT = void*>
  class Observer
  {
  public:
    virtual ~Observer() {}

    virtual void	update(const T& observable, const MsgT& msg) = 0;
  };
}

#endif /* UTIL_OBSERVER */
