//
//  Monster.cpp
//  RType
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "Monster.hh"
#include "TextureManager.hh"
#include "SoundManager.hh"

Monster::Monster(int monsterID)
{
    _monsterMap[1] = &Monster::initMonster1;
    _monsterMap[2] = &Monster::initMonster2;

    _animationDuration[1] = 0.5;
    _animationDuration[2] = 0.1;

    _monsterID = monsterID;
    _anim = 0;
    if (_monsterMap.find(_monsterID) != _monsterMap.end())
        (this->*_monsterMap[_monsterID])();
}

Monster::~Monster()
{
}

void Monster::update(sf::Vector2<float> pos)
{
#ifdef __APPLE__
  _sprite.setPosition((pos.x /1920) * 2880, (pos.y / 1080) * 1800);
#else
  _sprite.setPosition(pos.x - _sprite.getLocalBounds().width/2, pox.y - _sprite.getLocalBounds().height / 2);
#endif
    if (_clock.getElapsedTime().asSeconds() > _animationDuration[_monsterID])
    {
      _anim++;
      _clock.restart();
    }
  if (_animationMap.find(_anim) != _animationMap.end())
    _sprite.setTextureRect(_animationMap[_anim]);
  if (_anim >= _animationMap.size())
    _anim = 0;
}

void Monster::initMonster1()
{
    _texture = TextureManager::getInstance()->getTextureEnemy1();
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(4, 4, 252, 192));

    _sprite.scale(3.0, 3.0);

    _anim = 0;

    _animationMap[0] = sf::IntRect(1, 1, 62, 48);
    _animationMap[1] = sf::IntRect(66, 1, 63, 48);
    _animationMap[2] = sf::IntRect(131, 1, 63, 48);
    _animationMap[3] = sf::IntRect(66, 1, 63, 48);
}

void Monster::initMonster2()
{
    _texture = TextureManager::getInstance()->getTextureEnemy2();
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(20, 24, 84, 96));

    _sprite.scale(3.0, 3.0);

    _anim = 0;

    _animationMap[0] = sf::IntRect(5, 6, 21, 24);
    _animationMap[1] = sf::IntRect(38, 6, 21, 24);
    _animationMap[2] = sf::IntRect(71, 6, 21, 24);
    _animationMap[3] = sf::IntRect(104, 6, 21, 24);
    _animationMap[4] = sf::IntRect(137, 6, 21, 24);
    _animationMap[5] = sf::IntRect(170, 6, 21, 24);
    _animationMap[6] = sf::IntRect(203, 6, 21, 24);
    _animationMap[7] = sf::IntRect(236, 6, 21, 24);
}

void	Monster::playDeathSound() const
{
  if (_monsterID == 1)
    SoundManager::Play("explosion");
  else if (_monsterID == 2)
    SoundManager::Play("pop");
}
