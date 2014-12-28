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
      int id;
      for (std::map<int, RtypeProtocol::Room>::iterator it = _roomList.begin(); it != _roomList.end(); it++)
	{
	  std::string comp(reinterpret_cast<char*>(it->second.room_name));
	  if (comp == _view.getRoomName())
	    {
	      id = it->first;
	      std::cout << "find !!" << std::endl;
	      _listen->onRoomConnectFromMenu(id, _view.getRoomPass());
	      break;
	    }
	}
      break;
    case RtypeEvent::CREATE:
      std::cout << "Creating room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
      _listen->onCreateRoomFromMenu(_view.getRoomName(), _view.getRoomPass());
      break;
    case RtypeEvent::LEAVE:
      _listen->onRoomLeaveFromMenu();
      break;
    case RtypeEvent::READY:
      _listen->onUserReadyFromMenu();
      break;
    case RtypeEvent::GAMESTART:
      _listen->letStart();
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

void MenuController::joinRoom()
{
  //TO DO : change menuView to room view
  _view.setActualState(RtypeEvent::ROOMSTATE);
}

void	MenuController::setPlayersNameList(RtypeProtocol::Room room)
{
  std::string	str;

  for (size_t i = 0; i < room.nb_connected_users; i++)
    {
      str = reinterpret_cast<char*>(room.connected_users[i]);
      _playersName.push_back(str);
    }
}

void	MenuController::updatePlayerName()
{
  if (_playersName.size() >= 1)
    _view.setPlayerLabe1(_playersName[0]);
  if (_playersName.size() >= 2)
    _view.setPlayerLabe2(_playersName[1]);
  if (_playersName.size() >= 3)
    _view.setPlayerLabe3(_playersName[2]);
  if (_playersName.size() >= 4)
    _view.setPlayerLabe4(_playersName[3]);
  _playersName.clear();
}
