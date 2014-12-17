
#include <iostream>

#include "GameView.hh"
#include "Player.h"
#include "GameEnum.hh"

namespace	RType
{
  GameView::GameView()
  {
    _run = false;

    IObject *player = new Player(1);
    _map[0] = player;
  }

  GameView::~GameView()
  {

  }

  void	GameView::run(sf::RenderWindow& window)
  {
    _run = true;
    while (_run)
      {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	  /* network onKeyEvent(RType::LEFT) */
	  std::cout << "a remplir" << std::endl;
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
	  std::cout << "a remplir" << std::endl;
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
    std::map<int, IObject*>::iterator	it;

    for (it = _map.begin(); it != _map.end(); it++)
      {
	sf::Vector2<float>	pos = {100, 100};

	it->second->update(pos);
      }
  }

  void	GameView::render(sf::RenderWindow& window)
  {
    std::map<int, IObject*>::iterator	it;

    for (it = _map.begin(); it != _map.end(); it++)
      it->second->render(window);
  }
}
