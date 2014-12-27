//
//  PlayerPowerUp.cpp
//  RType
//
//  Created by Charles Fournier on 17/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "PlayerPowerUp.hh"
#include "TextureManager.hh"

PlayerPowerUp::PlayerPowerUp(int index)
{
    _index = index;
    _anim = 0;
    _texture = TextureManager::getInstance()->getTextureSheet2();
    _sprite.setTexture(_texture);
    _sprite.scale(2.0, 2.0);
    _powerUpMap[1] = &PlayerPowerUp::PowerUp1;
    _powerUpMap[2] = &PlayerPowerUp::PowerUp2;
    
    _animationDuration[1] = 0.07;
    _animationDuration[2] = 1.0;
    
    if (_powerUpMap.find(_index) != _powerUpMap.end())
        (this->*_powerUpMap[_index])();
}

PlayerPowerUp::~PlayerPowerUp()
{
    
}

void PlayerPowerUp::update(sf::Vector2<float> pos)
{
    _sprite.setPosition(pos);
    if (_clock.getElapsedTime().asSeconds() > _animationDuration[_index])
    {
        _anim++;
        _clock.restart();
    }
    if (_animationMap.find(_anim) != _animationMap.end())
        _sprite.setTextureRect(_animationMap[_anim]);
    if (_anim >= _animationMap.size())
        _anim = 0;
}


void PlayerPowerUp::PowerUp1()
{
    _animationMap.clear();
    _animationMap[0] = sf::IntRect(160, 35, 18, 16);
    _animationMap[1] = sf::IntRect(183, 35, 18, 16);
    _animationMap[2] = sf::IntRect(208, 35, 18, 16);
    _animationMap[3] = sf::IntRect(231, 35, 18, 16);
    _animationMap[4] = sf::IntRect(255, 35, 18, 16);
    _animationMap[5] = sf::IntRect(280, 35, 18, 16);
    _sprite.setTextureRect(_animationMap[0]);
}

void PlayerPowerUp::PowerUp2()
{
    
}

void PlayerPowerUp::setIndex(int index)
{
    _index = index;
}

int PlayerPowerUp::getIndex() const
{
    return _index;
}
