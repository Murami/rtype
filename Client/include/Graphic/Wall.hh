//
//  Wall.hh
//  RType
//
//  Created by Charles Fournier on 04/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__Wall__
#define __RType__Wall__

#include <string>
#include <SFML/Graphics.hpp>
#include "IObject.hh"

class Wall
{
public:
  Wall();
  ~Wall();
  
  void update();
  void render(sf::RenderWindow &window);
  
private:
  sf::Texture	_texture;
  sf::Texture	_rtexture;
  sf::Sprite	_bgUp1Sprite;
  sf::Sprite	_bgUp2Sprite;
  sf::Sprite	_bgDown1Sprite;
  sf::Sprite	_bgDown2Sprite;

};

#endif /* defined(__RType__ScrollingBackground__) */
