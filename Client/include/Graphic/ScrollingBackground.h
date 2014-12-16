//
//  ScrollingBackground.h
//  TestSFML
//
//  Created by Charles Fournier on 04/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__ScrollingBackground__
#define __TestSFML__ScrollingBackground__

#include <string>
#include <SFML/Graphics.hpp>
#include "IObject.h"

class ScrollingBackground : public IObject
{
public:
    ScrollingBackground(std::string filePath);
    virtual ~ScrollingBackground();

    virtual void update(sf::Vector2<float> pos);
    virtual void render(sf::RenderWindow &window);

    void setBgSpeed(float bgSpeed);
    void setBgRepeat(int repeat);

private:
    sf::Texture     _bg1Text;
    sf::Sprite      _bg1Sprite;
    sf::Sprite      _bg2Sprite;
    
    float           _bgSpeed;
    int             _repeat;
};

#endif /* defined(__TestSFML__ScrollingBackground__) */
