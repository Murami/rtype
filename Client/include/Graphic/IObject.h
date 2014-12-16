//
//  IObject.h
//  TestSFML
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_IObject_h
#define TestSFML_IObject_h

#include <SFML/Graphics.hpp>

class IObject {
public:
    virtual ~IObject() {};
    virtual void update(const sf::Vector2<float> pos) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
    
};

#endif
