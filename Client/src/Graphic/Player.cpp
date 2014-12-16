//
//  Ship.cpp
//  TestSFML
//
//  Created by Charles Fournier on 05/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "Player.h"
#include "TextureManager.h"

#ifdef __APPLE__
Player::Player(int nb)
{
    _nbPlayer = nb;
    _texture = TextureManager::getInstance()->getTextureShip();
    _sprite.setTexture(_texture);
    switch (nb) {
        case 1:
            _sprite.setTextureRect(sf::IntRect(3, 1, 107, 47));
            break;
        case 2:
            _sprite.setTextureRect(sf::IntRect(3, 67, 107, 47));
            break;
        case 3:
            _sprite.setTextureRect(sf::IntRect(3, 123, 107, 47));
            break;
        case 4:
            _sprite.setTextureRect(sf::IntRect(3, 180, 107, 47));
            break;
        default:
            _sprite.setTextureRect(sf::IntRect(3, 180, 107, 47));
            break;
    }
    _texture.setSmooth(false);
    _sprite.setPosition(100, 100);
}
#else
Player::Player(int nb)
{
    _nbPlayer = nb;
    _texture = TextureManager::getInstance()->getTextureShip();
    _sprite.setTexture(_texture);
    switch (nb) {
        case 1:
            _sprite.setTextureRect(sf::IntRect(3, 1, 32, 14));
            break;
        case 2:
            _sprite.setTextureRect(sf::IntRect(3, 20, 32, 14));
            break;
        case 3:
            _sprite.setTextureRect(sf::IntRect(3, 37, 32, 14));
            break;
        case 4:
            _sprite.setTextureRect(sf::IntRect(3, 54, 32, 14));
            break;
        default:
            _sprite.setTextureRect(sf::IntRect(3, 54, 32, 14));
            break;
    }
    _texture.setSmooth(false);
    _sprite.setPosition(100, 100);
}
#endif

Player::~Player()
{
    
}

void Player::update(const sf::Vector2<float> pos)
{
    _sprite.setPosition(pos.x, pos.y);
}