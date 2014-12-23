#include "Util/Vec2.hh"

namespace Util
{
  Vec2::Vec2() : x(0), y(0)
  {
  }

  Vec2::Vec2(const Vec2& vec) : x(vec.x), y(vec.y)
  {
  }

  Vec2::Vec2(float p_x, float p_y) : x(p_x), y(p_y)
  {
  }

  Vec2::~Vec2()
  {
  }

  const Vec2&	 Vec2::operator=(const Vec2& vec)
  {
    x = vec.x;
    y = vec.y;

    return (*this);
  }

  const Vec2&	 Vec2::operator+=(const Vec2& vec)
  {
    x += vec.x;
    y += vec.y;

    return (*this);
  }

  const Vec2&	 Vec2::operator-=(const Vec2& vec)
  {
    x -= vec.x;
    y -= vec.y;

    return (*this);
  }

  const Vec2&	 Vec2::operator*=(float factor)
  {
    x *= factor;
    y *= factor;

    return (*this);
  }

  const Vec2&	 Vec2::operator/=(float factor)
  {
    x /= factor;
    y /= factor;

    return (*this);
  }

  Vec2	 Vec2::operator+() const
  {
    return (*this);
  }

  Vec2	 Vec2::operator+(const Vec2& vec) const
  {
    return (Vec2(*this) += vec);
  }

  Vec2	 Vec2::operator-() const
  {
    return (Vec2(*this) *= -1);
  }

  Vec2	 Vec2::operator-(const Vec2& vec) const
  {
    return (Vec2(*this) -= vec);
  }

  Vec2	 Vec2::operator*(float factor) const
  {
    return (Vec2(*this) *= factor);
  }

  Vec2	 Vec2::operator/(float factor) const
  {
    return (Vec2(*this) /= factor);
  }

  float	 Vec2::dot(const Vec2& v1, const Vec2& v2)
  {
    return (v1.x * v2.x + v1.y * v2.y);
  }
};
