#include <iostream>
#include <cmath>
#include "Life.hh"
#include "TextureManager.hh"

Life::Life()
{
  _live = 3.0;
  _texture = TextureManager::getInstance()->getTextureLife();
  _sprite.setTexture(_texture);
  _sprite.setTextureRect(sf::IntRect(1, 3, 32, 28));
}

Life::~Life()
{

}

void Life::update(int live)
{
  float tmp = (live / 100) * 3;
  _live = std::round(tmp);
}

void Life::render(sf::RenderWindow &window)
{
  #ifdef __APPLE__
  if (_live >= 1)
    {
      _sprite.setPosition(100, 1750);
      window.draw(_sprite);
    }
  if (_live >= 2)
    {
      _sprite.setPosition(150, 1750);
      window.draw(_sprite);
    }
  if (_live >= 3)
    {
      _sprite.setPosition(200, 1750);
      window.draw(_sprite);
    }
  #else
  if (_live >= 1)
    {
      _sprite.setPosition(100, 1000);
      window.draw(_sprite);
    }
  if (_live >= 2)
    {
      _sprite.setPosition(150, 1000);
      window.draw(_sprite);
    }
  if (_live >= 3)
    {
      _sprite.setPosition(200, 1000);
      window.draw(_sprite);
    }
  #endif
}
