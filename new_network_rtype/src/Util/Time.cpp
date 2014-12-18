#include "Util/Time.hh"

#ifdef WIN32

#include <time.h>
#include <sys/timeb.h>

int	gettimeofday (struct timeval *tp, void /*tz*/)
{
  struct _timeb	timebuffer;

  _ftime (&timebuffer);

  tp->tv_sec = timebuffer.time;
  tp->tv_usec = timebuffer.millitm * 1000;

  return (0);
}

#elif __linux__
#include <sys/time.h>
#include <unistd.h>
#define Sleep(time) usleep(time * 1000)
#endif

namespace Util
{
  Time::Time() :
    _second(0),
    _microsecond(0)
  {
  }

  Time::Time(int second, int microsecond) :
    _second(second),
    _microsecond(microsecond)
  {
    normalize();
  }

  Time::Time(const Time& time) :
    _second(time._second),
    _microsecond(time._microsecond)
  {
  }

  Time::~Time()
  {
  }

  Time&	Time::operator=(const Time& time)
  {
    _second = time._second;
    _microsecond = time._microsecond;

    return (*this);
  }

  Time	Time::operator-() const
  {
    Time	time;

    time._second = -_second;
    time._microsecond = -_microsecond;

    return (time);
  }

  Time	Time::operator-(const Time& p_time) const
  {
    Time	time;

    time._second = _second - p_time._second;
    time._microsecond = _microsecond - p_time._microsecond;

    time.normalize();
    return (time);
  }

  Time	Time::operator+() const
  {
    Time	time;

    time._second = _second;
    time._microsecond = _microsecond;

    return (time);
  }

  Time	Time::operator+(const Time& p_time) const
  {
    Time	time;

    time._second = _second + p_time._second;
    time._microsecond = _microsecond + p_time._microsecond;

    time.normalize();
    return (time);
  }

  Time&	Time::operator+=(const Time& time)
  {
    _second += time._second;
    _microsecond += time._microsecond;

    normalize();
    return (*this);
  }

  Time&	Time::operator-=(const Time& time)
  {
    _second += time._second;
    _microsecond += time._microsecond;

    normalize();
    return (*this);
  }

  bool	Time::operator==(const Time& time) const
  {
    return (_second == time._second &&
	    _microsecond == time._microsecond);
  }

  bool	Time::operator!=(const Time& time) const
  {
    return (_second != time._second ||
	    _microsecond != time._microsecond);
  }

  bool	Time::operator<(const Time& time) const
  {
    return (_second < time._second ||
	    (_second == time._second &&
	     _microsecond < time._microsecond));
  }

  bool	Time::operator<=(const Time& time) const
  {
    return (_second < time._second ||
	    (_second == time._second &&
	     _microsecond <= time._microsecond));
  }

  bool	Time::operator>(const Time& time) const
  {
    return (_second > time._second ||
	    (_second == time._second &&
	   _microsecond > time._microsecond));
  }

  bool	Time::operator>=(const Time& time) const
  {
    return (_second > time._second ||
	    (_second == time._second &&
	   _microsecond >= time._microsecond));
  }

  void	Time::normalize()
  {
    _second += _microsecond / 1000000;
    _microsecond += _microsecond % 1000000;

    if (_microsecond < 0 && _second > 0)
      {
	_microsecond += 1000000;
	_second -= 1;
      }
    else if (_microsecond > 0 && _second < 0)
      {
	_microsecond -= 1000000;
	_second += 1;
      }
  }

  unsigned int	getCurrentTime()
  {
    struct timeval time;

    gettimeofday(&time, 0);
    return (time.tv_usec / 1000);
  }

  void		sleep(unsigned int millisecond)
  {
    Sleep(millisecond);
  }
};
