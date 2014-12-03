//
//  MenuController.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__MenuController__
#define __TestSFML__MenuController__

#include "MenuEnum.h"
#include "IObserver.h"
#include "MenuView.h"

class MenuController : public IObserver
{

public:
    MenuController(MenuView &view);
    ~MenuController();
    void update(eButton idCallback);
    void manageUpdate(eButton idCallback);
    
private:
    MenuView _view;
};


#endif /* defined(__TestSFML__MenuController__) */
