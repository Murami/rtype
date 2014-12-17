//
//  MenuController.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __TestSFML__MenuController__
#define __TestSFML__MenuController__

#include "IMenuListener.hh"
#include "MenuEnum.hh"
#include "IObserver.hh"
#include "MenuView.hh"

class MenuController : public IObserver
{

public:
    MenuController(MenuView &view);
    virtual ~MenuController();
  void update(RTypeEvent::eButton idCallback);
  void manageUpdate(RTypeEvent::eButton idCallback);

   void setMenuListener(IMenuListener *);

private:
    MenuView _view;
    IMenuListener *_listen;
};


#endif /* defined(__TestSFML__MenuController__) */
