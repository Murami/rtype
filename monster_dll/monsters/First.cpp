
#include "First.hh"

First::First()
{
  _name = "First";
  _life = 100;
  _x = 0;
  _y = 0;
}

First::~First()
{
  
}

std::uint32_t	First::basicAttack() const
{
  return (1);
}

std::uint32_t	First::specialAttack() const
{
  return (20);
}

/* extern */

extern "C" std::string	get_monster_name()
{
  return ("First");
}

extern "C" First*	instantiate_plugin()
{
  return (new First());
}
