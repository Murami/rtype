#ifndef PHYSIC_WORLD_BODY
#define PHYSIC_WORLD_BODY

namespace Physic
{
  class WorldBody
  {
    friend class World;

  protected:
    virtual void	update(float time) = 0;
  };
};

#endif /* PHYSIC_WORLD_BODY */
