
#include "GameController.hh"
#include "GameView.hh"

GameController::GameController(GameView& view)
  : _view(view)
{
    
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
