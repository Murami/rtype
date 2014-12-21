//
//  ScrollingBackground.cpp
//  RType
//
//  Created by Charles Fournier on 04/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "ScrollingBackground.hh"
#include <iostream>

ScrollingBackground::ScrollingBackground(std::string filePath)
{
    _bgSpeed = 0.7;
    
    _bg1Text.loadFromFile(filePath);
    _bg1Text.setSmooth(false);
    _bg1Sprite.setTexture(_bg1Text);
    _bg1Sprite.setPosition(0, 0);
    _bg2Sprite.setTexture(_bg1Text);
    _bg2Sprite.setPosition(_bg1Sprite.getPosition().x + _bg1Sprite.getLocalBounds().width, 0);
    _repeat = 1;
}

ScrollingBackground::~ScrollingBackground()
{ }

void ScrollingBackground::update(sf::Vector2<float>)
{
    if ((_bg1Sprite.getPosition().x + (_bg1Sprite.getLocalBounds().width * _repeat)) < 0)
        _bg1Sprite.setPosition(_bg2Sprite.getPosition().x + _bg2Sprite.getLocalBounds().width, 0);
    else
     _bg1Sprite.setPosition((_bg1Sprite.getPosition().x - _bgSpeed), 0);
    
    if (_repeat == 1) {
        if ((_bg2Sprite.getPosition().x + (_bg2Sprite.getLocalBounds().width * _repeat)) < 0)
            _bg2Sprite.setPosition(_bg1Sprite.getPosition().x + _bg1Sprite.getLocalBounds().width, 0);
        else
            _bg2Sprite.setPosition((_bg2Sprite.getPosition().x - _bgSpeed), 0);
    }
}

void ScrollingBackground::setBgSpeed(float bgSpeed)
{
    _bgSpeed = bgSpeed;
}

void ScrollingBackground::setBgRepeat(int repeat)
{
    _repeat = repeat;
}

void ScrollingBackground::render(sf::RenderWindow &window)
{
    window.draw(_bg1Sprite);
    window.draw(_bg2Sprite);
}
