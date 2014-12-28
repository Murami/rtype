//
//  MenuController.hh
//  RType
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef __RType__MenuController__
#define __RType__MenuController__

#include <map>
#include "IMenuListener.hh"
#include "MenuEnum.hh"
#include "IMenuObserver.hh"
#include "MenuView.hh"
#include "RtypeProtocol.hh"

class MenuController : public IMenuObserver
{

public:
  MenuController(MenuView &view);
  virtual ~MenuController();
  void update(RtypeEvent::eButton idCallback);
  void manageUpdate(RtypeEvent::eButton idCallback);
  
  void setMenuListener(IMenuListener *);
  void addToRoomList(RtypeProtocol::Room room);
  void deleteFromRoomList(RtypeProtocol::Room room);
  void updateRoomList();
  void joinRoom();
  void	setPlayersNameList(RtypeProtocol::Room);
  void	updatePlayerName();
  
private:
  MenuView& _view;
  IMenuListener *_listen;
  std::map<int, RtypeProtocol::Room>	_roomList;
  std::string				_playersName[4];
};

#endif /* defined(__RType__MenuController__) */
