#include "Timer.hh"
#include "TimerObserver.hh"
#include "Service.hh"

namespace Network
{

  Timer::Timer()
  {
    _service = NULL;
  }

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

  void		Timer::setService(Service * service)
  {
    _service = service;
  }

  void		Timer::cancel()
  {
    if (_service != NULL)
      _service->deleteTimeout(*this);
  }

} /* namespace Network */
