#ifndef UTIL_TIME_HH
#define UTIL_TIME_HH

namespace Util
{
  class Time
  {
  private:
    int	_second;
    int	_microsecond;

  public:
    Time();
    Time(int second, int microsecond);
    Time(const Time& time);
    ~Time();

    Time&	operator=(const Time& time);

    Time	operator-() const;
    Time	operator-(const Time& time) const;
    Time	operator+() const;
    Time	operator+(const Time& time) const;

    Time&	operator+=(const Time& time);
    Time&	operator-=(const Time& time);

    bool	operator==(const Time& time) const;
    bool	operator!=(const Time& time) const;
    bool	operator<(const Time& time) const;
    bool	operator<=(const Time& time) const;
    bool	operator>(const Time& time) const;
    bool	operator>=(const Time& time) const;

  private:
    void	normalize();
  };
};

#endif /* UTIL_TIME_HH */
