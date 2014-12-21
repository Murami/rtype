
#include "Camera.hh"

Camera::Camera(float x, float y)
  : _x(x),
    _y(y)
{
}

Camera::~Camera()
{ 
}

void	Camera::setPosition(float x, float y)
{
  _x = x;
  _y = y;
}

void	Camera::setPosition(sf::Vector2<float> pos)
{
  _x = pos.x;
  _y = pos.y;
}

sf::Vector2<float>	Camera::getPosition() const
{
  sf::Vector2<float>	res;

  res.x = _x;
  res.y = _y;
  return (res);
}

float	Camera::getX() const
{
  return (_x);  
}

float	Camera::getY() const
{
  return (_y);
}
