//
//  Monster.hh
//  RType
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__Monster__
#define __RType__Monster__

#include "AObject.hh"
#include <map>

class Monster : public AObject {
    
public:
  Monster(int monsterID);
  virtual ~Monster();
    
  virtual void	update(sf::Vector2<float> pos);
  virtual void	playDeathSound() const;

private:
    int                                 _monsterID;
    unsigned int                        _anim;
    std::map<int, void(Monster::*)()>   _monsterMap;
    std::map<int, sf::IntRect>          _animationMap;
    std::map<int, float>                _animationDuration;
    sf::Clock                           _clock;

private:
    void initMonster1();
    void initMonster2();
};

#endif /* defined(__RType__Monster__) */
