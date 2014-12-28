//
//  IObject.hh
//  RType
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef RType_IObject_h
#define RType_IObject_h

#include <SFML/Graphics.hpp>

class IObject {
public:
  virtual			~IObject() {};
  virtual void			update(const sf::Vector2<float> pos) = 0;
  virtual void			updateAnim() = 0;
  virtual void			render(sf::RenderWindow &window) = 0;
  virtual void			setPosition(sf::Vector2<float>) = 0;
  virtual sf::Vector2<float>	getPosition() const = 0;
  virtual void			setSpeed(sf::Vector2<float>) = 0;
  virtual sf::Vector2<float>	getSpeed() const = 0;
  virtual bool&			networkUpdated() = 0;
  virtual void			playDeathSound() const = 0;
};

#endif
