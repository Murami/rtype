//
//  LittleRocket.cpp
//  TestSFML
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "LittleRocket.h"
#include "TextureManager.h"

#ifdef __APPLE__
LittleRocket::LittleRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(830, 350, 53, 27));
    else
        _sprite.setTextureRect(sf::IntRect(890, 350, 53, 27));
}
#else
LittleRocket::LittleRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(249, 105, 16, 8));
    else
        _sprite.setTextureRect(sf::IntRect(267, 105, 16, 8));
}
#endif

LittleRocket::~LittleRocket()
{
    
}

void LittleRocket::update(sf::Vector2<float> pos)
{
    if (_friendly == true)
        _sprite.setPosition(_sprite.getPosition().x + 7, _sprite.getPosition().y);
    else
        _sprite.setPosition(_sprite.getPosition().x - 7, _sprite.getPosition().y);
}
