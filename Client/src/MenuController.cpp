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
      std::cout << "Joining room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
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

void MenuController::addToRoomList(RtypeProtocol::Room room)
{
  _roomList[room.id] = room;
  std::cout << "Add room : " << room.room_name << std::endl;
}

void MenuController::deleteFromRoomList(RtypeProtocol::Room room)
{
  if (_roomList.find(room.id) != _roomList.end())
    {
      _roomList.erase(room.id);
      std::cout << "erase room : " << room.room_name << std::endl;
    }

}
