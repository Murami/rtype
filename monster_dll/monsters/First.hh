
#ifndef _FIRST_HH_
# define _FIRST_HH_

# include "AMonster.hh"

class	First : public RType::AMonster
{
public:
  First();
  ~First();

  std::uint32_t		basicAttack() const;
  std::uint32_t		specialAttack() const;
};

# if defined (WIN32) || defined (_WIN32)
extern "C"
{
	__declspec(dllexport) std::string	get_monster_name();
	__declspec(dllexport) First*		instantiate_plugin();
}
# endif /* WIN32 */

#endif
