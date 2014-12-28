//
//  Wall.cpp
//  RType
//
//  Created by Charles Fournier on 04/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "Wall.hh"
#include "TextureManager.hh"
#include <iostream>

Wall::Wall()
{
  _rtexture = TextureManager::getInstance()->getTextureRWall();
  _texture = TextureManager::getInstance()->getTextureWall();
  _bgUp1Sprite.setTexture(_rtexture);

#ifdef __APPLE__
  _bgUp1Sprite.setPosition(0, 0);
  _bgDown1Sprite.setPosition(0, 1760);
#else
  _bgUp1Sprite.setPosition(0, 0);
  _bgDown1Sprite.setPosition(0, 1050);
#endif



  _bgUp2Sprite.setTexture(_rtexture);
  _bgUp2Sprite.setPosition(_bgUp1Sprite.getPosition().x + _bgUp1Sprite.getLocalBounds().width, _bgUp1Sprite.getPosition().y);

  _bgDown1Sprite.setTexture(_texture);
  _bgDown2Sprite.setTexture(_texture);
  _bgDown2Sprite.setPosition(_bgDown1Sprite.getPosition().x + _bgDown1Sprite.getLocalBounds().width, _bgDown1Sprite.getPosition().y);
  
}

Wall::~Wall()
{ }

void Wall::update()
{
  if ((_bgUp1Sprite.getPosition().x + (_bgUp1Sprite.getLocalBounds().width) < 0))
    _bgUp1Sprite.setPosition(_bgUp2Sprite.getPosition().x + _bgUp2Sprite.getLocalBounds().width, _bgUp2Sprite.getPosition().y);
  else
    _bgUp1Sprite.setPosition((_bgUp1Sprite.getPosition().x - 0.5), _bgUp1Sprite.getPosition().y);

  if ((_bgUp2Sprite.getPosition().x + (_bgUp2Sprite.getLocalBounds().width) < 0))
    _bgUp2Sprite.setPosition(_bgUp1Sprite.getPosition().x + _bgUp1Sprite.getLocalBounds().width, _bgUp1Sprite.getPosition().y);
  else
    _bgUp2Sprite.setPosition((_bgUp2Sprite.getPosition().x - 0.5), _bgUp2Sprite.getPosition().y);



  if ((_bgDown1Sprite.getPosition().x + (_bgDown1Sprite.getLocalBounds().width) < 0))
    _bgDown1Sprite.setPosition(_bgDown2Sprite.getPosition().x + _bgDown2Sprite.getLocalBounds().width, _bgDown2Sprite.getPosition().y);
  else
    _bgDown1Sprite.setPosition((_bgDown1Sprite.getPosition().x - 0.5), _bgDown1Sprite.getPosition().y);

  if ((_bgDown2Sprite.getPosition().x + (_bgDown2Sprite.getLocalBounds().width) < 0))
    _bgDown2Sprite.setPosition(_bgDown1Sprite.getPosition().x + _bgDown1Sprite.getLocalBounds().width, _bgDown1Sprite.getPosition().y);
  else
    _bgDown2Sprite.setPosition((_bgDown2Sprite.getPosition().x - 0.5), _bgDown2Sprite.getPosition().y);

  

//   if ((_bg1UpSprite.getPosition().x + (_bgUp1Sprite.getLocalBounds().width * _repeat)) < 0)
//     _bgUp1Sprite.setPosition(_bg2Sprite.getPosition().x + _bg2Sprite.getLocalBounds().width, 0);
//   else
//     _bgUp1Sprite.setPosition((_bgUp1Sprite.getPosition().x - _bgSpeed), 0);
  
//     if (_repeat == 1) {
//         if ((_bg2Sprite.getPosition().x + (_bg2Sprite.getLocalBounds().width * _repeat)) < 0)
//             _bg2Sprite.setPosition(_bg1Sprite.getPosition().x + _bg1Sprite.getLocalBounds().width, 0);
//         else
//             _bg2Sprite.setPosition((_bg2Sprite.getPosition().x - _bgSpeed), 0);
//     }
}

void Wall::render(sf::RenderWindow &window)
{
     window.draw(_bgUp1Sprite);
    window.draw(_bgUp2Sprite);
    window.draw(_bgDown1Sprite);
    window.draw(_bgDown2Sprite);
}
