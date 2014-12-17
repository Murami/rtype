//
//  LittleRocket.h
//  TestSFML
//
//  Created by Charles Fournier on 10/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__LittleRocket__
#define __TestSFML__LittleRocket__

#include "AObject.hh"

class LittleRocket : public AObject {
    
public:
    LittleRocket(bool friendly = true);
    virtual ~LittleRocket();
    virtual void update(sf::Vector2<float> pos);
    
private:
    bool _friendly;
    
};

#endif /* defined(__TestSFML__LittleRocket__) */
