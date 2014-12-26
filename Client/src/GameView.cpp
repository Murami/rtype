
#include <iostream>

#include "GameView.hh"
#include "Player.hh"
#include "GameEnum.hh"
#include "SoundManager.hh"
#include "BigRocket.hh"
#include "Mutex.hh"

GameView::GameView()
{
  _run = false;
  _backgroundVector.push_back(new ScrollingBackground("./res/Game/background_game.jpg"));
  _backgroundVector.push_back(new ScrollingBackground("./res/Game/planets.png"));
  _backgroundVector[1]->setBgSpeed(0.5);

  IObject *player = new BigRocket(true);

  _objectMap[0] = player;
}

GameView::~GameView()
{
  // std::map<int, IObject*>::iterator		itObj;
  // std::vector<ScrollingBackground*>::iterator	itBack;

  // for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
  //   delete (itObj->second);
  // for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
  //   delete (*itBack);
}

void	GameView::run(sf::RenderWindow& window, Util::Mutex *mutex)
{
  size_t	mask;

  _run = true;
  while (_run)
    {
      mask = RtypeEvent::DEFAULT;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	mask += RtypeEvent::LEFT;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	mask += RtypeEvent::RIGHT;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	mask += RtypeEvent::UP;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	mask += RtypeEvent::DOWN;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	mask += RtypeEvent::SPACE;

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	_run = false;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	std::cout << "a remplir" << std::endl;
      this->notify(mask);
      window.clear();
      this->update();
      this->render(window);
      //mutex->unlock();
      window.display();
      //mutex->lock();
    }
}

void	GameView::add(int id, IObject* obj)
{
  if (_objectMap.find(id) == _objectMap.end())
    _objectMap[id] = obj;
}

void	GameView::erase(int id)
{
  if (_objectMap.find(id) != _objectMap.end())
    {
      delete ((_objectMap.find(id))->second);
      _objectMap.erase(id);
    }
}

void	GameView::update()
{
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    (*itBack)->update(sf::Vector2<float>(0, 0));
}

void	GameView::updateById(int id, RtypeProtocol::Position pos)
{
  if (_objectMap.find(id) != _objectMap.end())
    {
      sf::Vector2<float> tmp(pos.x, pos.y);
      _objectMap[id]->update(tmp);
    }
}

void	GameView::render(sf::RenderWindow& window)
{
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    (*itBack)->render(window);
  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    itObj->second->render(window);
}
