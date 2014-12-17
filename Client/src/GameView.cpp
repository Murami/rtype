
#include <iostream>

#include "GameView.hh"
#include "Player.h"
#include "GameEnum.hh"
#include "SoundManager.hh"
#include "BigRocket.h"

namespace	RType
{
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
	  /* network onKeyEvent(RType::LEFT) */
	  {
	    RType::SoundManager::Stop("stage1");
	    RType::SoundManager::Play("pause");
	  }
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	  /* network onKeyEvent(RType::RIGHT) */
	  std::cout << "a remplir" << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	  /* network onKeyEvent(RType::UP) */
	  std::cout << "a remplir" << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	  /* network onKeyEvent(RType::DOWN) */
	  std::cout << "a remplir" << std::endl;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	  /* network onKeyEvent(RType::SPACE) */
	  RType::SoundManager::Play("bip");
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	  /* network onKeyEvent(RType::ESCAPE) */
	  _run = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	  /* network onKeyEvent(RType::ENTER) */
	  std::cout << "a remplir" << std::endl;
	window.clear();
	this->update();
	this->render(window);
	window.display();
      }
  }

  void	GameView::update()
  {
    std::map<int, IObject*>::iterator		itObj;
    std::vector<ScrollingBackground*>::iterator	itBack;

    for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
      {
	sf::Vector2<float>	pos = {100, 100};

	itObj->second->update(pos);
      }
    for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
      (*itBack)->update(sf::Vector2<float>(0, 0));
  }

  void	GameView::render(sf::RenderWindow& window)
  {
    std::map<int, IObject*>::iterator		itObj;
    std::vector<ScrollingBackground*>::iterator	itBack;

    for (itObj = _objectMap.begin(); itObj != _objectMap.end(); itObj++)
      itObj->second->render(window);
    for (itBack = _backgroundVector.begin(); itBack != _backgroundVector.end(); itBack++)
      (*itBack)->render(window);
  }
}
