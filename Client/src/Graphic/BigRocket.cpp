//
//  Rocket.cpp
//  RType
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "BigRocket.hh"
#include "TextureManager.hh"
#include "SoundManager.hh"

BigRocket::BigRocket(bool friendly)
{
    _friendly = friendly;
    _texture = TextureManager::getInstance()->getTextureRocket();
    _sprite.setTexture(_texture);
    
#ifdef __APPLE__
    _sprite.scale(3.0, 3.0);
#endif
    
    if (_friendly == true)
        _sprite.setTextureRect(sf::IntRect(168, 137, 48, 12));
    else
        _sprite.setTextureRect(sf::IntRect(316, 137, 48, 12));
    SoundManager::Play("laser2");
}

BigRocket::~BigRocket()
{
    
}

void BigRocket::update(sf::Vector2<float> pos)
{
    _sprite.setPosition(pos);
}


