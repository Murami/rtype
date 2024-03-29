#include <iostream>

#include "GameView.hh"
#include "GameEnum.hh"
#include "SoundManager.hh"
#include "TextureManager.hh"
#include "Mutex.hh"

GameView::GameView()
{
  _run = false;
  _gameEnd = false;
  _backgroundVector.push_back(new ScrollingBackground("./res/Game/background_game.jpg"));
  _backgroundVector.push_back(new ScrollingBackground("./res/Game/planets.png"));
  _backgroundVector[1]->setBgSpeed(0.5);
}

GameView::~GameView()
{
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    delete (itObj->second);
  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    delete (*itBack);
}

void	GameView::run(sf::RenderWindow& window, Util::Mutex *mutex)
{
  size_t	mask;
  sf::Clock	clock;

  SoundManager::Play("stage1", true);
  SoundManager::Play("horde");
  window.setMouseCursorVisible(false);
  window.setFramerateLimit(60);
  _run = true;
  while (_run)
    {
      this->updateSpawn();
      this->updateDestroy();
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

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
	_run = false;
	this->onRoomExit();
	this->onExit();
      }
      this->notify(mask);
      window.clear();
      this->update(clock.restart().asSeconds());
      this->render(window);
      mutex->unlock();
      window.display();
      mutex->lock();
    }

  SoundManager::Stop();
  if (_gameWin == true)
    {
      _texture = TextureManager::getInstance()->getTextureWin();
      SoundManager::Play("stageClear");
    }
  else
    {
      _texture = TextureManager::getInstance()->getTextureLoose();
      SoundManager::Play("gameOver");
    }
  _sprite.setTexture(_texture);
  _sprite.setPosition(0, 0);
  while (_gameEnd == true)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
	  this->onRoomExit();
	  this->onExit();
	  break;
	}
      window.clear();
      window.draw(_sprite);
      window.display();
    }
  
  SoundManager::Stop();
}

void	GameView::stop()
{
  SoundManager::Stop();
  _run = false;
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
      _objectMap[id]->playDeathSound();
      delete ((_objectMap.find(id))->second);
      _objectMap.erase(id);
    }
}

void	GameView::emptyMap()
{
  std::map<int, IObject*>::iterator		itObj;

  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    delete (itObj->second);
  _objectMap.clear();
}

void	GameView::update(float time)
{
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  _wall.update();

  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    (*itBack)->update(sf::Vector2<float>(0, 0));

  sf::Vector2<float>	pos;

  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    {
      if (itObj->second->networkUpdated() == false)
	{
#ifdef __APPLE__
	  pos = itObj->second->getPosition();
	  pos.x = (pos.x / 2880) * 1920;
	  pos.y = (pos.y / 1800) * 1080;
	  pos = pos + (itObj->second->getSpeed() * time);
#else
	  pos = itObj->second->getPosition() + (itObj->second->getSpeed() * time);
#endif
	  itObj->second->update(pos);
	}
      else
	itObj->second->networkUpdated() = false;
      itObj->second->updateAnim();
    }
}

bool	GameView::updateById(int id, RtypeProtocol::Position pos)
{
  if (_objectMap.find(id) != _objectMap.end())
    {
      sf::Vector2<float>	tmp(pos.x, pos.y);
      sf::Vector2<float>	speed(pos.speedX, pos.speedY);

      _objectMap[id]->networkUpdated() = true;
      _objectMap[id]->setSpeed(speed);
      _objectMap[id]->update(tmp);
      return (true);
    }
  return (false);
}

void	GameView::render(sf::RenderWindow& window)
{
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    (*itBack)->render(window);
  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    itObj->second->render(window);
  _wall.render(window);
  _life.render(window);
}

void	GameView::updateLife(int, int life)
{
  _life.update(life);
}

void	GameView::isGameEnd(bool end)
{
  _gameEnd = end;
  _run = false;
}

void	GameView::isGameIsWin(bool win)
{
  _gameWin = win;
}
