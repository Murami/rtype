
#include "Second.hh"

Second::Second()
{
  _name = "Second";
  _life = 100;
  _x = 0;
  _y = 0;
}

Second::~Second()
{
  
}

std::uint32_t	Second::basicAttack() const
{
  return (2);
}

std::uint32_t	Second::specialAttack() const
{
  return (15);
}

/* extern */

extern "C" std::string	get_monster_name()
{
  return ("Second");
}

extern "C" Second*	instantiate_plugin()
{
  return (new Second());
}
