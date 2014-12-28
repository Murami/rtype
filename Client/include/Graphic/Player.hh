//
//  Player.hh
//  RType
//
//  Created by Charles Fournier on 05/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__Player__
#define __RType__Player__

#include <string>
#include <SFML/Graphics.hpp>
#include "AObject.hh"
#include "PlayerPowerUp.hh"

class Player : public AObject
{
public:
    Player(int nb = 1);
    virtual ~Player();
    virtual void update(const sf::Vector2<float> pos);
  virtual void updateAnim();
    virtual void render(sf::RenderWindow &window);
    
    void	setPower(int power);
    int		getPower() const;

private:
    int             _nbPlayer;
    PlayerPowerUp   _powerUp;
};

#endif /* defined(__RType__Player__) */
