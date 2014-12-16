//
//  Rocket.cpp
//  TestSFML
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "BigRocket.h"
#include "TextureManager.h"

#ifdef __APPLE__
BigRocket::BigRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(558, 457, 159, 40));
    else
        _sprite.setTextureRect(sf::IntRect(1053, 457, 159, 40));
}
#else
BigRocket::BigRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(168, 137, 48, 12));
    else
        _sprite.setTextureRect(sf::IntRect(316, 137, 48, 12));
}
#endif

BigRocket::~BigRocket()
{
    
}

void BigRocket::update(sf::Vector2<float> pos)
{
    if (_friendly == true)
        _sprite.setPosition(_sprite.getPosition().x + 5, _sprite.getPosition().y);
    else
        _sprite.setPosition(_sprite.getPosition().x - 5, _sprite.getPosition().y);
}


