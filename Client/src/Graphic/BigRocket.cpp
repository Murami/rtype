//
//  Rocket.cpp
//  TestSFML
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "BigRocket.h"
#include "TextureManager.h"

BigRocket::BigRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);
    
#ifdef __APPLE__
    _sprite.scale(2.0, 2.0);
#endif
    
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(168, 137, 48, 12));
    else
        _sprite.setTextureRect(sf::IntRect(316, 137, 48, 12));
}

BigRocket::~BigRocket()
{
    
}

void BigRocket::update(sf::Vector2<float> pos)
{
    _sprite.setPosition(pos);
    
//    if (_friendly == true)
//        _sprite.setPosition(_sprite.getPosition().x + 7, _sprite.getPosition().y);
//    else
//        _sprite.setPosition(_sprite.getPosition().x - 7, _sprite.getPosition().y);
}


