//
//  TextureManager.cpp
//  RType
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "TextureManager.hh"
#include <iostream>

TextureManager *TextureManager::_instance = NULL;

TextureManager::TextureManager()
{
    
}

TextureManager::~TextureManager()
{
}

TextureManager *TextureManager::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new TextureManager();
        _instance->loadTexture();
    }
    return _instance;
}

void TextureManager::loadTexture()
{
    _ship.loadFromFile("./res/Game/r-typesheet42.gif");
    _sheet2.loadFromFile("./res/Game/r-typesheet2.gif");
    _rocket.loadFromFile("./res/Game/r-typesheet1.gif");
    _enemy1.loadFromFile("./res/Game/r-typesheet26.gif");
    _enemy2.loadFromFile("./res/Game/r-typesheet5.gif");
    _enemy3.loadFromFile("./res/Game/r-typesheet9.gif");
    _life.loadFromFile("./res/Game/r-typesheet30a.gif");
    _wall.loadFromFile("./res/Game/r-typesheet54.gif");
    _rwall.loadFromFile("./res/Game/r-typesheet45.gif");
}

sf::Texture TextureManager::getTextureShip() const
{
    return _ship;
}

sf::Texture TextureManager::getTextureRocket() const
{
    return _rocket;
}

sf::Texture TextureManager::getTextureEnemy1() const
{
    return _enemy1;
}

sf::Texture TextureManager::getTextureEnemy2() const
{
    return _enemy2;
}

sf::Texture TextureManager::getTextureEnemy3() const
{
    return _enemy3;
}

sf::Texture TextureManager::getTextureSheet2() const
{
    return _sheet2;
}

sf::Texture TextureManager::getTextureLife() const
{
  return _life;
}

sf::Texture TextureManager::getTextureWall() const
{
  return _wall;
}

sf::Texture TextureManager::getTextureRWall() const
{
  return _rwall;
}

