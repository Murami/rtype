#include "Timer.hh"
#include "TimerObserver.hh"

namespace Network
{

  Timer::Timer() {}

  Timer::~Timer() {}

  void	Timer::setTimeout(const std::chrono::system_clock::duration& time)
  {
    std::chrono::system_clock::time_point	now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration		epochTime = now.time_since_epoch();

    _time = time + epochTime;
  }

  const std::chrono::system_clock::duration&	Timer::getTime(void) const
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
