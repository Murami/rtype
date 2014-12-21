
#include "GameController.hh"
#include "GameView.hh"

GameController::GameController(GameView& view)
  : _view(view)
{
  (void)_view;
}

GameController::~GameController()
{

}

void	GameController::update()
{
  
}

void	GameController::setGameListener(IGameListener* listener)
{
  _listener = listener;
}
