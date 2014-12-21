//
//  PlayerPowerUp.hh
//  RType
//
//  Created by Charles Fournier on 17/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__PlayerPowerUp__
#define __RType__PlayerPowerUp__

#include <map>
#include "AObject.hh"

class PlayerPowerUp : public AObject
{
public:
  PlayerPowerUp(int index);
  virtual ~PlayerPowerUp();
  virtual void update(sf::Vector2<float> pos);
  
  void	setIndex(int index);
  int	getIndex() const;

private:
    int						_index;
    size_t					_anim;
    std::map<int, void(PlayerPowerUp::*)()>     _powerUpMap;
    std::map<int, sf::IntRect>                  _animationMap;
    std::map<int, float>                        _animationDuration;
    sf::Clock                                   _clock;
    
private:
    void PowerUp1();
    void PowerUp2();
    
};

#endif /* defined(__RType__PlayerPowerUp__) */
