//
//  MenuView.h
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#ifndef TestSFML_MenuView_h
# define TestSFML_MenuView_h

# include <TGUI/TGUI.hpp>
# include <SFML/Graphics.hpp>
# include <map>
# include <string>
# include "Observable.hh"
# include "MenuEnum.hh"

class MenuView : public Observable
{
public:
  MenuView(sf::RenderWindow &window);
  ~MenuView();
    
  void initLogin();
  void initMenu();
  void initRoomSelect();
  void initRoom();
  void initSetting();
    
  void run(sf::RenderWindow &window);
  void stop();
    
  void setActualState(RtypeEvent::eMenuState state);
  RtypeEvent::eMenuState getActualState() const;
    
public:
  std::string getLogin() const;
  std::string getRoomName() const;
  std::string getRoomPass() const;
    
    
  void setRoomName(std::string name);
  void setPlayerLabe1(std::string name);
  void setPlayerLabe2(std::string name);
  void setPlayerLabe3(std::string name);
  void setPlayerLabe4(std::string name);
    
private:
  void prevState();
    
private:
  tgui::Gui           *_loginGui;
  tgui::Gui           *_menuGui;
  tgui::Gui           *_roomSelectGui;
  tgui::Gui           *_roomGui;
  tgui::Gui *_settingGui;
  tgui::EditBox::Ptr  _editBoxUsername;
  tgui::EditBox::Ptr  _editBoxRoomName;
  tgui::EditBox::Ptr  _editBoxRoomPass;
  tgui::ListBox::Ptr  _listRoom;
  tgui::Label::Ptr    _labelPlayer1;
  tgui::Label::Ptr    _labelPlayer2;
  tgui::Label::Ptr    _labelPlayer3;
  tgui::Label::Ptr    _labelPlayer4;
  tgui::ChatBox::Ptr  _chatBox;
  tgui::Slider::Ptr _slider;
    
  RtypeEvent::eMenuState          _actualState;
    
  std::map< RtypeEvent::eMenuState, tgui::Gui* > _stateToGui;
  bool                _run;
    
  int _width;
  int _height;
};

#endif
