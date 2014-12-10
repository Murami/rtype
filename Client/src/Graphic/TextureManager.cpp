//
//  TextureManager.cpp
//  TestSFML
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "TextureManager.h"
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
        _instance->loadRetinaTexture();
    }
    return _instance;
}

void TextureManager::loadRetinaTexture()
{
    _ship.loadFromFile("/Users/Charles/Desktop/R-Type_Ressources/r-typesheet42@2.gif");
    _rocket.loadFromFile("/Users/Charles/Desktop/R-Type_Ressources/r-typesheet1@2.png");
}

void TextureManager::loadTexture()
{
    _ship.loadFromFile("/Users/Charles/Desktop/R-Type_Ressources/r-typesheet42.gif");
    _rocket.loadFromFile("/Users/Charles/Desktop/R-Type_Ressources/r-typesheet1.gif");
}

sf::Texture TextureManager::getTextureShip() const
{
    return _ship;
}

sf::Texture TextureManager::getTextureRocket() const
{
    return _rocket;
}