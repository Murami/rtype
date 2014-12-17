//
//  MenuController.cpp
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "MenuController.hh"
#include <iostream>

MenuController::MenuController(MenuView &view) : _view(view)
{ }

MenuController::~MenuController()
{ }

void MenuController::update(RTypeEvent::eButton idCallback)
{
    this->manageUpdate(idCallback);
}

void MenuController::manageUpdate(RTypeEvent::eButton idCallback)
{
  switch (idCallback)
    {
    case RTypeEvent::LOGIN:
      std::cout << "Login : " << _view.getLogin() << std::endl;
      _listen->onConnectFromMenu(_view.getLogin());
      break;
    case RTypeEvent::JOIN:
      std::cout << "Joining room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
      break;
    case RTypeEvent::CREATE:
      std::cout << "Creating room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
      break;
    default:
      break;
    }
}

void MenuController::setMenuListener(IMenuListener *listen)
{
   _listen = listen;
}
