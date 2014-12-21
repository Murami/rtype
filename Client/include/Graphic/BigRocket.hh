//
//  Rocket.hh
//  RType
//
//  Created by Charles Fournier on 09/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__Rocket__
#define __RType__Rocket__

#include <SFML/Graphics.hpp>
#include "AObject.hh"

class BigRocket : public AObject {

public:
    BigRocket(bool friendly = true);
    virtual ~BigRocket();
    virtual void update(sf::Vector2<float> pos);
    
private:
    bool _friendly;
};

#endif /* defined(__RType__Rocket__) */
