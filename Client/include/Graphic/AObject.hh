//
//  AObject.h
//  TestSFML
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__AObject__
#define __TestSFML__AObject__

#include "IObject.hh"

class AObject : public IObject {
    
public:
    AObject();
    virtual ~AObject();
    virtual void update(const sf::Vector2<float> pos = {0, 0});
    virtual void render(sf::RenderWindow &window);

public:
    virtual sf::Vector2<float> getPosition() const;
    virtual void setPosition(sf::Vector2<float> position);
    
protected:
    sf::Sprite  _sprite;
    sf::Texture _texture;

};

#endif /* defined(__TestSFML__AObject__) */
