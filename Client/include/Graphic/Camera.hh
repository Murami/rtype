
#ifndef _CAMERA_HH_
# define _CAMERA_HH_

# include <SFML/Graphics.hpp>

class	Camera
{
public:
  Camera(float x = 0, float y = 0);
  ~Camera();

  void	setPosition(float x, float y);
  void	setPosition(sf::Vector2<float>);

  sf::Vector2<float>	getPosition() const;
  float			getX() const;
  float			getY() const;

private:
  float	_x;
  float	_y;
};

#endif /* _CAMERA_HH_ */
