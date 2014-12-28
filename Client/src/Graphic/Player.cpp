//
//  Player.cpp
//  RType
//
//  Created by Charles Fournier on 05/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include <map>
#include <iostream>
#include "Player.hh"
#include "TextureManager.hh"
#include "SoundManager.hh"

Player::Player(int nb) : _powerUp(1)
{
    std::cout << "Constructeur player" << std::endl;
    _nbPlayer = nb;
    _texture = TextureManager::getInstance()->getTextureShip();
    _sprite.setTexture(_texture);
    
    _sprite.scale(2.0, 2.0);    
    
    std::map<int, sf::IntRect> playerSprite;
    
    playerSprite[1] = sf::IntRect(3, 1, 32, 14);
    playerSprite[2] = sf::IntRect(3, 20, 32, 14);
    playerSprite[3] = sf::IntRect(3, 37, 32, 14);
    playerSprite[4] = sf::IntRect(3, 54, 32, 14);
    
    if (playerSprite.find(nb) == playerSprite.end())
        nb = 1;

    //  _sprite.setOrigin(_sprite.getLocalBounds().width, _sprite.getLocalBounds().height);

    _sprite.setTextureRect(playerSprite[nb]);
    _texture.setSmooth(false);
    _sprite.setPosition(100, 100);
    _powerUp.setPosition(sf::Vector2<float>(_sprite.getPosition().x + _sprite.getLocalBounds().width,
					    _sprite.getPosition().y + _sprite.getLocalBounds().height / 2));
}

Player::~Player()
{
  SoundManager::Play("mort");    
}

void Player::update(const sf::Vector2<float> pos)
{
// #ifdef __APPLE__
//   float x, y;
//   x = (pos.x / 1920) * 2880;
//   y = (pos.y / 1920) * 1800;
//   _sprite.setPosition(x, y);
// #else
  _sprite.setPosition(pos.x, pos.y);
  sf::Vector2<float> tmp(pos.x + _sprite.getLocalBounds().width * 2, pos.y + _sprite.getLocalBounds().height - 10);
  _powerUp.update(tmp);
  //  #endif
}

void Player::updateAnim()
{
  _powerUp.updateAnim();
}

void Player::render(sf::RenderWindow &window)
{
    window.draw(_sprite);
    _powerUp.render(window);
}

void Player::setPower(int power)
{
    _powerUp.setIndex(power);
}

int Player::getPower() const
{
    return _powerUp.getIndex();
}
