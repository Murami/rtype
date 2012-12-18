
#include <iostream>

#include "GameView.hh"
#include "Player.hh"
#include "GameEnum.hh"
#include "SoundManager.hh"
#include "BigRocket.hh"

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
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    delete (itObj->second);
  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    delete (*itBack);
}

void	GameView::run(sf::RenderWindow& window)
{
  _run = true;
  while (_run)
    {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	/* network onKeyEvent(RTypeEvent::LEFT) */
	{
	  SoundManager::Stop("scoring");
	  SoundManager::Play("stage8");
	}
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	/* network onKeyEvent(RTypeEvent::RIGHT) */
	std::cout << "a remplir" << std::endl;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	/* network onKeyEvent(RTypeEvent::UP) */
	std::cout << "a remplir" << std::endl;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	/* network onKeyEvent(RTypeEvent::DOWN) */
	std::cout << "a remplir" << std::endl;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	/* network onKeyEvent(RTypeEvent::SPACE) */
	SoundManager::Play("bip");
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	/* network onKeyEvent(RTypeEvent::ESCAPE) */
	_run = false;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	/* network onKeyEvent(RTypeEvent::ENTER) */
	std::cout << "a remplir" << std::endl;
      window.clear();
      this->update();
      this->render(window);
      window.display();
    }
}

void	GameView::add(int id, IObject* obj)
{
  if (_objectMap.find(id) == _objectMap.end())
    _objectMap[id] = obj;
}

void	GameView::update()
{
  std::map<int, IObject*>::iterator		itObj;
  std::vector<ScrollingBackground*>::iterator	itBack;

  for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
    (*itBack)->update(sf::Vector2<float>(0, 0));
  for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
    {
      sf::Vector2<float>	pos = {100, 100};

      itObj->second->update(pos);
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
