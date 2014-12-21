
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

void	GameController::spawnEntity()
{

}

void	GameController::updateEntityPosition(int id, RtypeProtocol::Position pos)
{
  (void)id;
  (void)pos;
}

void	GameController::update()
{
  
}

void	GameController::setGameListener(IGameListener* listener)
{
  _listener = listener;
}
