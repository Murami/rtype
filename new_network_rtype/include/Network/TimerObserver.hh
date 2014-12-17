#ifndef TIMER_OBSERVER_HH
# define TIMER_OBSERVER_HH

namespace Network
{

  class Timer;

  class TimerObserver
  {
  public:
    virtual void onTimeout(Timer &) = 0;
  };

} /* namespace Network */

#endif /* TIMER_OBSERVER_HH */
