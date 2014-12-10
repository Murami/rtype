//
//  TextureManager.h
//  TestSFML
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__TextureManager__
#define __TestSFML__TextureManager__

#include <SFML/Graphics.hpp>

class TextureManager {
public:
    
    static TextureManager *getInstance();
    
    
    sf::Texture getTextureShip() const;
    sf::Texture getTextureRocket() const;
    
    void loadRetinaTexture();
    void loadTexture();
    
private:
    sf::Texture _ship;
    sf::Texture _rocket;
    
    
private:
    static TextureManager *_instance;
    TextureManager();
    ~TextureManager();


};

#endif /* defined(__TestSFML__TextureManager__) */
