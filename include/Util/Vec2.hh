#ifndef UTIL_VEC2
#define UTIL_VEC2

namespace Util
{
  class Vec2
  {
  public:
    float	x;
    float	y;

  public:
    Vec2();
    Vec2(const Vec2& vec);
    Vec2(float p_x, float p_y);
    ~Vec2();

    const Vec2&	operator=(const Vec2& vec);
    const Vec2&	operator+=(const Vec2& vec);
    const Vec2&	operator-=(const Vec2& vec);
    const Vec2&	operator*=(float factor);
    const Vec2&	operator/=(float factor);
    Vec2	operator+() const;
    Vec2	operator+(const Vec2& vec) const;
    Vec2	operator-() const;
    Vec2	operator-(const Vec2& vec) const;
    Vec2	operator*(float factor) const;
    Vec2	operator/(float factor) const;

    static float	dot(const Vec2& v1, const Vec2& v2);
  };
};

#endif /* UTIL_VEC2 */
