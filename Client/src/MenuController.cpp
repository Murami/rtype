//
//  MenuController.cpp
//  RType
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "MenuController.hh"
#include "RtypeProtocol.hh"
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
      //_listen->onRoomConnectFromMenu(_view.getLogin());
      //      _listen->onRoomConnectFromMenu(_view.getLogin());
      break;
    case RtypeEvent::CREATE:
      std::cout << "Creating room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
      _listen->onCreateRoomFromMenu(_view.getRoomName(), _view.getRoomPass());
      break;
    case RtypeEvent::LEAVE:
      _listen->onRoomLeaveFromMenu();
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
  this->updateRoomList();
}

void MenuController::updateRoomList()
{
  _view.resetRoomList();
  for (std::map<int, RtypeProtocol::Room>::iterator it = _roomList.begin(); it != _roomList.end(); it++)
    _view.addRoom(std::string(reinterpret_cast<char*>(it->second.room_name)));
}

void MenuController::deleteFromRoomList(RtypeProtocol::Room room)
{
  if (_roomList.find(room.id) != _roomList.end())
    {
      _roomList.erase(room.id);
      std::cout << "erase room : " << room.room_name << std::endl;
      this->updateRoomList();
    }
}
