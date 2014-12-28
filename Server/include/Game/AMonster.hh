
#ifndef _MONSTER_HH_
# define _MONSTER_HH_

# include <string>
# include <cstdint>
# include "APlugin.hh"

class	AMonster : public PluginManager::APlugin
{
public:
  virtual ~AMonster() {}

  std::uint32_t		getLevel() const;
  bool			isAlive() const;
  void			takeDamage(std::uint32_t damage);
  virtual std::uint32_t	basicAttack() const = 0;
  virtual std::uint32_t	specialAttack() const = 0;

  /* getters et setters */
  void			x(std::int32_t);
  std::int32_t		x() const;
  void			y(std::int32_t);
  std::int32_t		y() const;

protected:
  std::uint32_t	_life;
  std::uint32_t	_level;
  std::int32_t	_x;
  std::int32_t	_y;
};

#endif /* _MONSTER_HH_ */
