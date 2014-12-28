//
//  Rocket.hh
//  RType
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__Life__
#define __RType__Life__

#include <SFML/Graphics.hpp>
#include "AObject.hh"

class Life {

public:
  Life();
  ~Life();
  void update(int live);
  void render(sf::RenderWindow &window);
  
private:
  float		_live;
  sf::Texture	_texture;
  sf::Sprite	_sprite;

};

#endif /* defined(__RType__Rocket__) */
