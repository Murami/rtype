#include "Life.hh"
#include "TextureManager.hh"

Life::Life()
{
  _live = 3;
  _texture = TextureManager::getInstance()->getTextureLife();
  _sprite.setTexture(_texture);
  _sprite.setTextureRect(sf::IntRect(1, 3, 32, 28));
}

Life::~Life()
{

}

void Life::update(size_t live)
{
  _live = live;
}

void Life::render(sf::RenderWindow &window)
{
  #ifdef __APPLE__
  _sprite.setPosition(100, 1750);
  window.draw(_sprite);
  _sprite.setPosition(150, 1750);
  window.draw(_sprite);
  _sprite.setPosition(200, 1750);
  window.draw(_sprite);
  #else
  _sprite.setPosition(0, 0);
  window.draw(_sprite);
  _sprite.setPosition(0, 0);
  window.draw(_sprite);
  _sprite.setPosition(0, 0);
  window.draw(_sprite);
  #endif
}
