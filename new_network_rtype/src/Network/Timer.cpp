#include "Timer.hh"
#include "TimerObserver.hh"

namespace Network
{

  Timer::Timer() {}

  Timer::~Timer() {}

  void	Timer::setTime(int second, int microsecond)
  {
    _time = Util::Time(second, microsecond);
  }

  void	Timer::setTime(const Util::Time& time)
  {
    _time = time;
  }

  const Util::Time&	Timer::getTime(void) const
  {
    return (_time);
  }

  void		Timer::setObserver(TimerObserver * observer)
  {
    _observer = observer;
  }

  void		Timer::notify()
  {
    _observer->onTimeout(*this);
  }

} /* namespace Network */
