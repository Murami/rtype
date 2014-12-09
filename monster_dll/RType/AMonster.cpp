
#include "AMonster.hh"

namespace	RType
{
  std::uint32_t	AMonster::getLevel() const
  {
    return (_level);
  }

  bool	AMonster::isAlive() const
  {
    if (_life == 0)
      return (false);
    return (true);
  }

  void	AMonster::takeDamage(std::uint32_t damage)
  {
    if (_life - damage <= 0)
      _life = 0;
    else
      _life -= damage;    
  }

  /* getters et setters */
  void	x(std::uint32_t x)
  {
    _x = x;
  }

  std::uint32_t		x() const
  {
    return (_x);
  }

  void	y(std::uint32_t y)
  {
    _y = y;
  }

  std::uint32_t		y() const
  {
    return (_y);
  }
}
