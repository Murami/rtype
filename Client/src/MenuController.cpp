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

void MenuController::update(RtypeEvent::eButton idCallback)
{
    this->manageUpdate(idCallback);
}

void MenuController::manageUpdate(RtypeEvent::eButton idCallback)
{
  switch (idCallback)
    {
    case RtypeEvent::LOGIN:
      std::cout << "Login : " << _view.getLogin() << std::endl;
      _listen->onConnectFromMenu(_view.getLogin());
      break;
    case RtypeEvent::JOIN:
      // Creer un RtypeProtocol::RoomConnect ICI et l'envoyer
      std::cout << "Joining room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
      _listen->onRoomConnectFromMenu(_view.getLogin());
      break;
    case RtypeEvent::CREATE:
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
