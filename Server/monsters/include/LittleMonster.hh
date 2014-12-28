#ifndef LITTLE_MONSTER
#define LITTLE_MONSTER

#include "Monster.hh"

namespace Game
{
  class LittleMonster : public Monster
  {
  public:
    LittleMonster(Core& game);
    ~LittleMonster();

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
	__declspec(dllexport) void*		instantiate_plugin(void*);
}
# endif /* WIN32 */

#endif /* LITTLE_MONSTER */
