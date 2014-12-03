//
//  MenuEnum.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_MenuEnum_h
#define TestSFML_MenuEnum_h

enum eButton {
    LOGIN = 1,
    PLAY,
    SETTINGS,
    SCORES,
    CREDITS,
    CREATE,
    JOIN,
    READY,
    LISTCHOICE,
    BACK
};

enum eMenuState {
    LOGINSTATE = 1,
    MENUSTATE,
    ROOMSELECTSTATE,
    ROOMSTATE,
    UNKNOWSTATE,
};

#endif
