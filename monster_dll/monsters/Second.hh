
#ifndef _SECOND_HH_
# define _SECOND_HH_

# include "AMonster.hh"

class	Second : public	AMonster
{
public:
  Second();
  ~Second();

  std::uint32_t		basicAttack() const;
  std::uint32_t		specialAttack() const;
};

# if defined (WIN32) || defined (_WIN32)
extern "C"
{
	__declspec(dllexport) std::string	get_monster_name();
	__declspec(dllexport) Second*		instantiate_plugin();
}
# endif /* WIN32 */

#endif
