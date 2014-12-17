//
//  PlayerPowerUp.h
//  TestSFML
//
//  Created by Charles Fournier on 17/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__PlayerPowerUp__
#define __TestSFML__PlayerPowerUp__

#include <map>
#include "AObject.h"

class PlayerPowerUp : public AObject
{
public:
    PlayerPowerUp(int index);
    virtual ~PlayerPowerUp();
    virtual void update(sf::Vector2<float> pos);

    void setIndex(int index);
    void setPosition(float posX, float posY);
    int getIndex() const;
    sf::Vector2<float> getPosition() const;
    
private:
    int _index;
    int _anim;
    std::map<int, void(PlayerPowerUp::*)()>     _powerUpMap;
    std::map<int, sf::IntRect>                  _animationMap;
    std::map<int, float>                        _animationDuration;
    sf::Clock                                   _clock;
    
private:
    void PowerUp1();
    void PowerUp2();
    
};

#endif /* defined(__TestSFML__PlayerPowerUp__) */
