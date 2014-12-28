#ifndef BIG_MONSTER
#define BIG_MONSTER

#include "Monster.hh"

namespace Game
{
  class BigMonster : public Monster
  {
  public:
    BigMonster(Core& game);
    ~BigMonster();

    void	update(float time);
    void	onCollide(Entity& entity);
    void	onCollide(Player& player);
    void	onCollide(Projectile& projectile);
    void	onCollide(Monster& monster);
    void	onCollide(DestroyableSet& set);
  };
};

# if defined (WIN32) || defined (_WIN32)
extern "C"
{
	__declspec(dllexport) std::string	get_monster_name();
	__declspec(dllexport) BigMonster*	instantiate_plugin(void*);
}
# endif /* WIN32 */

#endif /* BIG_MONSTER */
