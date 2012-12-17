#include "Time.hh"

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

  int	Time::getSecond() const
  {
    return (_second);
  }

  int	Time::getMicrosecond() const
  {
    return (_microsecond);
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
};
