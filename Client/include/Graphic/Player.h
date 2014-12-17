//
//  Ship.h
//  TestSFML
//
//  Created by Charles Fournier on 05/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__Player__
#define __TestSFML__Player__

#include <string>
#include <SFML/Graphics.hpp>
#include "AObject.h"
#include "PlayerPowerUp.h"

class Player : public AObject
{

public:
    Player(int nb = 1);
    virtual ~Player();
    virtual void update(const sf::Vector2<float> pos);
    virtual void render(sf::RenderWindow &window);
    
    void setPower(int power);
    int     getPower() const;

private:
    int             _nbPlayer;
    PlayerPowerUp   _powerUp;
};

#endif /* defined(__TestSFML__Player__) */
