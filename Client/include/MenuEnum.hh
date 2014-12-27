//
//  MenuEnum.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_MenuEnum_h
#define TestSFML_MenuEnum_h

namespace	RtypeEvent
{
  enum eButton {
    LOGIN = 1,
    PLAY,
    SETTINGS,
    SCORES,
    CREDITS,
    CREATE,
    LEAVE,
    JOIN,
    READY,
    LISTCHOICE,
    APPLY,
    BACK,
    GAMESTART
  };

  enum eMenuState {
    LOGINSTATE = 1,
    MENUSTATE,
    ROOMSELECTSTATE,
    ROOMSTATE,
    SETTINGSTATE,
    UNKNOWSTATE
  };
}

#endif
