#ifndef TIMER_HH
# define TIMER_HH

# include <chrono>
# include "Time.hh"

namespace Network
{
  typedef std::chrono::duration<int, std::ratio<1> >   duration_second;
  typedef std::chrono::duration<int, std::milli >      duration_millisecond;
  typedef std::chrono::duration<int, std::micro >      duration_microsecond;

  class TimerObserver;

  class Timer
  {
  public:
    Timer();
    ~Timer();

    void					setTimeout(const std::chrono::system_clock::duration& time);
    const std::chrono::system_clock::duration&	getTime(void) const;

    void					setObserver(TimerObserver * observer);
    void					notify();

  private:
    std::chrono::system_clock::duration		_time;
    TimerObserver *				_observer;
  };

} /* namespace Network */

#endif /* TIMER_HH */
