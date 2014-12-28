//
//  LittleRocket.cpp
//  RType
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "LittleRocket.hh"
#include "TextureManager.hh"
#include "SoundManager.hh"

LittleRocket::LittleRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);

#ifdef __APPLE__
    _sprite.scale(3.0, 3.0);
#endif
    
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(249, 105, 16, 8));
    else
        _sprite.setTextureRect(sf::IntRect(267, 105, 16, 8));
    SoundManager::Play("laser1");
}

LittleRocket::~LittleRocket()
{
    
}

void LittleRocket::update(sf::Vector2<float> pos)
{
#ifdef __APPLE__
  _sprite.setPosition((pos.x / 1920) * 2880, (pos.y / 1080) * 1800);
#else
  _sprite.setPosition(pos);  
#endif
}
