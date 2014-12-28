#include "Game/Camera.hh"

namespace Game
{
  Camera::Camera(Core& game) :
    Entity(game, false, T_CAMERA)
  {
  }

  Camera::~Camera()
  {
  }

  void	Camera::update(float /*time*/)
  {

  }
};
