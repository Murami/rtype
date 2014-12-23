#ifndef GAME_CAMERA
#define GAME_CAMERA

#include "Entity.hh"

namespace Game
{
  class Camera : public Entity
  {
  public:
    Camera(Core& game);
    ~Camera();

    void	update(float time);
  };
};

#endif /* GAME_CAMERA */
