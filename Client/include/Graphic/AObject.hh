//
//  AObject.hh
//  RType
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__AObject__
#define __RType__AObject__

#include "IObject.hh"

class AObject : public IObject {
    
public:
  AObject();
  virtual ~AObject();
  virtual void update(const sf::Vector2<float> pos = {0, 0});
  virtual void updateAnim();
  virtual void render(sf::RenderWindow &window);
  
public:
  virtual sf::Vector2<float>	getPosition() const;
  virtual void			setPosition(sf::Vector2<float> position);
  virtual sf::Vector2<float>	getSpeed() const;
  virtual void			setSpeed(sf::Vector2<float>);
  virtual bool&			networkUpdated();

protected:
  sf::Sprite		_sprite;
  sf::Texture		_texture;
  sf::Vector2<float>	_speed;
  bool			_networkUpdated;
};

#endif /* defined(__RType__AObject__) */
