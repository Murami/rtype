#ifndef TIMER_HH
# define TIMER_HH

# include "Time.hh"

namespace Network
{

  class TimerObserver;

  class Timer
  {
  public:
    Timer();
    ~Timer();

    void		setTime(int second, int microsecond);
    void		setTime(const Util::Time& time);
    const Util::Time&	getTime(void) const;

    void		setObserver(TimerObserver * observer);
    void		notify();

  private:
    Util::Time			_time;
    TimerObserver *		_observer;
  };

} /* namespace Network */

#endif /* TIMER_HH */
