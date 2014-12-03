//
//  MenuController.cpp
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "MenuController.h"
#include <iostream>

MenuController::MenuController(MenuView &view) : _view(view)
{ }

MenuController::~MenuController()
{ }

void MenuController::update(eButton idCallback)
{
    this->manageUpdate(idCallback);
}

void MenuController::manageUpdate(eButton idCallback)
{
    switch (idCallback) {
        case LOGIN:
            std::cout << "Login : " << _view.getLogin() << std::endl;
            break;
        case JOIN:
            std::cout << "Joining room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
            break;
        case CREATE:
            std::cout << "Creating room : " << _view.getRoomName() << " with password : " << _view.getRoomPass() << std::endl;
            break;
        default:
            break;
    }
}