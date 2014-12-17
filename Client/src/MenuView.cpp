//
//  MenuView.cpp
//  TestSFML
//
//  Created by Charles Fournier on 02/12/2014.
//  Copyright (c) 2014 Charles Fournier. All rights reserved.
//

#include "MenuView.hh"

#ifdef __APPLE__
static const char *blackConf = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/widgets/Black.conf";
static const char *backgroundLogin = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/login.jpg";
static const char *backgroundMenu = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/Menu.jpg";
static const char *backgroundRoomSelect = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/roomSelect.jpg";
static const char *backgroundRoom = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/room.jpg";
static const char *fontPath = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/Tr2n.ttf";
static const char *chatFont = "/Users/Charles/Documents/Tek 3/TestSFML/TestSFML/DejaVuSans.ttf";
#else
static const char *blackConf = "./res/widgets/Black.conf";
static const char *backgroundLogin = "./res/login.jpg";
static const char *backgroundMenu = "./res/Menu.jpg";
static const char *backgroundRoomSelect = "./res/roomSelect.jpg";
static const char *backgroundRoom = "./res/room.jpg";
static const char *fontPath = "./res/Tr2n.ttf";
static const char *chatFont = "./res/DejaVuSans.ttf";
#endif



MenuView::MenuView(sf::RenderWindow &window)
{
    _run = false;
    _actualState = RTypeEvent::LOGINSTATE;

    _width = sf::VideoMode::getDesktopMode().width;
    _height = sf::VideoMode::getDesktopMode().height;

#ifdef __APPLE__
    if (_width == 1920 && _height == 1200)
    {
        _width = 2880;
        _height = 1800;
    }
#endif

    _loginGui = new tgui::Gui(window);
    _menuGui = new tgui::Gui(window);
    _roomSelectGui = new tgui::Gui(window);
    _roomGui = new tgui::Gui(window);

    _stateToGui[RTypeEvent::LOGINSTATE] = _loginGui;
    _stateToGui[RTypeEvent::MENUSTATE] = _menuGui;
    _stateToGui[RTypeEvent::ROOMSELECTSTATE] = _roomSelectGui;
    _stateToGui[RTypeEvent::ROOMSTATE] = _roomGui;

    initLogin();
    initMenu();
    initRoomSelect();
    initRoom();

    window.setKeyRepeatEnabled(false);
}

MenuView::~MenuView()
{
    _loginGui->removeAllWidgets();
    _menuGui->removeAllWidgets();
    _roomSelectGui->removeAllWidgets();
    _roomGui->removeAllWidgets();
}

void MenuView::initLogin()
{
    _loginGui->setGlobalFont(fontPath);

    tgui::Picture::Ptr picture(*_loginGui);
    picture->load(backgroundLogin);
    picture->setSize(_width, _height);

    _loginGui->add(_editBoxUsername);
    _editBoxUsername->load(blackConf);
    _editBoxUsername->setSize((0.27 * _width), (0.044 * _height));
    _editBoxUsername->setPosition((_width / 2) - (0.138 * _width), (0.77 * _height));
    _editBoxUsername->setMaximumCharacters(16);

    tgui::Button::Ptr button(*_loginGui);
    button->load(blackConf);
    button->setSize((0.09 * _width), (0.033 * _height));
    button->setPosition((_width / 2) - (0.045 * _width), (0.83 * _height));
    button->setText("Login");
    button->setTextSize(45);
    //button->setTextSize(60);
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setCallbackId(RTypeEvent::LOGIN);
}

void MenuView::initMenu()
{
    _menuGui->setGlobalFont(fontPath);

    tgui::Picture::Ptr picture(*_menuGui);
    picture->load(backgroundMenu);
    picture->setSize(_width, _height);

    tgui::Button::Ptr playButton(*_menuGui);
    playButton->load(blackConf);
    playButton->setTextSize(70);
//    playButton->setTextSize(90);
    playButton->setSize((0.20 * _width), (0.12 * _height));
    playButton->setPosition((0.115 * _width), (0.455 * _height));
    playButton->setText("Play");
    playButton->bindCallback(tgui::Button::LeftMouseClicked);
    playButton->setCallbackId(RTypeEvent::PLAY);

    tgui::Button::Ptr settingsButton(*_menuGui);
    settingsButton->load(blackConf);
    settingsButton->setTextSize(70);
//    settingsButton->setTextSize(90);
    settingsButton->setSize((0.20 * _width), (0.12 * _height));
    settingsButton->setPosition((0.115 * _width), (0.63 * _height));
    settingsButton->setText("Settings");
    settingsButton->bindCallback(tgui::Button::LeftMouseClicked);
    settingsButton->setCallbackId(RTypeEvent::SETTINGS);

    tgui::Button::Ptr scoresButton(*_menuGui);
    scoresButton->load(blackConf);
    scoresButton->setTextSize(70);
//    scoresButton->setTextSize(90);
    scoresButton->setSize((0.20 * _width), (0.12 * _height));
    scoresButton->setPosition((0.682 * _width), (0.455 * _height));
    scoresButton->setText("Scores");
    scoresButton->bindCallback(tgui::Button::LeftMouseClicked);
    scoresButton->setCallbackId(RTypeEvent::SCORES);

    tgui::Button::Ptr creditsButton(*_menuGui);
    creditsButton->load(blackConf);
    creditsButton->setTextSize(70);
//    creditsButton->setTextSize(90);
    creditsButton->setSize((0.20 * _width), (0.12 * _height));
    creditsButton->setPosition((0.682 * _width), (0.619 * _height));
    creditsButton->setText("Credits");
    creditsButton->bindCallback(tgui::Button::LeftMouseClicked);
    creditsButton->setCallbackId(RTypeEvent::CREDITS);
}

void MenuView::initRoomSelect()
{
    _roomSelectGui->setGlobalFont(fontPath);

    tgui::Picture::Ptr picture(*_roomSelectGui);
    picture->load(backgroundRoomSelect);
    picture->setSize(_width, _height);

    _roomSelectGui->add(_editBoxRoomName);
    _editBoxRoomName->load(blackConf);
    _editBoxRoomName->setSize((0.277 * _width), (0.044 * _height));
    _editBoxRoomName->setPosition((_width / 3) * 2 - (0.069 * _width), (0.388 * _height));

    _roomSelectGui->add(_editBoxRoomPass);
    _editBoxRoomPass->load(blackConf);
    _editBoxRoomPass->setSize((0.277 * _width), (0.044 * _height));
    _editBoxRoomPass->setPosition((_width / 3) * 2 - (0.069 * _width), (0.61 * _height));

    _roomSelectGui->add(_listRoom);
    _listRoom->setItemHeight(35);
//    _listRoom->setItemHeight(55);
    _listRoom->load(blackConf);
    _listRoom->setSize((0.34 * _width), (0.388 * _height));
    _listRoom->setPosition((_width / 3) - (0.225 * _width), (0.316 * _height));
    _listRoom->addItem("room1");
    _listRoom->addItem("room2");
    _listRoom->addItem("room3");
    _listRoom->bindCallback(tgui::Button::LeftMouseClicked);
    _listRoom->setCallbackId(RTypeEvent::LISTCHOICE);
    _listRoom->setTextColor(sf::Color::Cyan);

    tgui::Button::Ptr createButton(*_roomSelectGui);
    createButton->load(blackConf);
    createButton->setSize((0.190 * _width), (0.05 * _height));
    createButton->setPosition((_width / 3) - (0.095 * _width), (0.833 * _height));
    createButton->setText("Join Room");
    createButton->setTextSize(45);
//    createButton->setTextSize(60);
    createButton->bindCallback(tgui::Button::LeftMouseClicked);
    createButton->setCallbackId(RTypeEvent::JOIN);

    tgui::Button::Ptr joinButton(*_roomSelectGui);
    joinButton->load(blackConf);
    joinButton->setSize((0.190 * _width), (0.05 * _height));
    joinButton->setPosition((_width / 3) * 2 - (0.095 * _width), (0.833 * _height));
    joinButton->setText("Create Room");
    joinButton->setTextSize(45);
//    joinButton->setTextSize(60);
    joinButton->bindCallback(tgui::Button::LeftMouseClicked);
    joinButton->setCallbackId(RTypeEvent::CREATE);


    tgui::Button::Ptr selectButton(*_roomSelectGui);
    selectButton->load(blackConf);
    selectButton->setSize(100, 100);
    selectButton->setPosition(_width / 2 - (0.017 * _width), _height / 2);
    selectButton->setText("Select");
    selectButton->setTextSize(20);
//    selectButton->setTextSize(40);
    selectButton->bindCallback(tgui::Button::LeftMouseClicked);
    selectButton->setCallbackId(RTypeEvent::LISTCHOICE);
}

void MenuView::initRoom()
{
    sf::Font font;
    font.loadFromFile(chatFont);

    _roomGui->setGlobalFont(fontPath);

    tgui::Picture::Ptr picture(*_roomGui);
    picture->load(backgroundRoom);
    picture->setSize(_width, _height);

    tgui::Button::Ptr button(*_roomGui);
    button->load(blackConf);
    button->setSize((0.0902 * _width), (0.044 * _height));
    button->setPosition((_width / 2) - (0.045 * _width), (0.851 * _height));
    button->setText("Ready");
    button->setTextSize(45);
//    button->setTextSize(60);
    button->bindCallback(tgui::Button::LeftMouseClicked);
    button->setCallbackId(RTypeEvent::READY);

    _roomGui->add(_chatBox);
    _chatBox->load(blackConf);
    _chatBox->setSize((0.399 * _width), (0.194 * _height));
    _chatBox->setTextSize(22);
//    _chatBox->setTextSize(30);
    _chatBox->setTextFont(font);
    _chatBox->setTextColor(sf::Color::Cyan);
    _chatBox->setPosition((_width / 3) - (0.173 * _width), (0.611 * _height));
    _chatBox->addLine("Player1 : Salut");
    _chatBox->addLine("Player2 : Yo");
    _chatBox->addLine("Player2 : Pret ?");
    _chatBox->addLine("Player2 : Go");

    _roomGui->add(_labelPlayer1);
    _labelPlayer1->load(blackConf);
    _labelPlayer1->setSize((0.104 * _width), (0.027 * _height));
    _labelPlayer1->setPosition((0.173 * _width), (0.333 * _height));
    _labelPlayer1->setTextColor(sf::Color::Cyan);
    _labelPlayer1->setText("Player1");
    _labelPlayer1->setTextSize(25);
//    _labelPlayer1->setTextSize(50);

    _roomGui->add(_labelPlayer2);
    _labelPlayer2->load(blackConf);
    _labelPlayer2->setSize((0.104 * _width), (0.027 * _height));
    _labelPlayer2->setPosition((0.381 * _width), (0.333 * _height));
    _labelPlayer2->setTextColor(sf::Color::Cyan);
    _labelPlayer2->setText("Player2");
    _labelPlayer2->setTextSize(25);
//    _labelPlayer2->setTextSize(50);

    _roomGui->add(_labelPlayer3);
    _labelPlayer3->load(blackConf);
    _labelPlayer3->setSize((0.104 * _width), (0.027 * _height));
    _labelPlayer3->setPosition((0.173 * _width), (0.444 * _height));
    _labelPlayer3->setTextColor(sf::Color::Cyan);
    _labelPlayer3->setText("Player3");
    _labelPlayer3->setTextSize(25);
//    _labelPlayer3->setTextSize(50);

    _roomGui->add(_labelPlayer4);
    _labelPlayer4->load(blackConf);
    _labelPlayer4->setSize((0.104 * _width), (0.027 * _height));
    _labelPlayer4->setPosition((0.381 * _width), (0.444 * _height));
    _labelPlayer4->setTextColor(sf::Color::Cyan);
    _labelPlayer4->setText("Player4");
    _labelPlayer4->setTextSize(25);
//    _labelPlayer4->setTextSize(50);


    //    tgui::Picture::Ptr themePreview(*_roomGui);
    //    themePreview->setSize(300, 600);

}

void MenuView::run(sf::RenderWindow &window)
{
    _run = true;
    while (_run == true && window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                if (_actualState == RTypeEvent::LOGINSTATE)
                {
                    _run = false;
                    window.close();
                }
                else
                {
                    this->prevState();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && _actualState == RTypeEvent::LOGINSTATE && _editBoxUsername->getText() != "")
            {
                _actualState = RTypeEvent::MENUSTATE;
                this->notify(RTypeEvent::LOGIN);
            }
            _stateToGui[_actualState]->handleEvent(event);
        }
        tgui::Callback callback;
        while (_stateToGui[_actualState]->pollCallback(callback))
        {
            switch (callback.id)
            {
	    case RTypeEvent::LOGIN:
	      if (_editBoxUsername->getText() == "")
		break;
	      _actualState = RTypeEvent::MENUSTATE;
	      this->notify(RTypeEvent::LOGIN);
	      break;
	    case RTypeEvent::PLAY:
	      _actualState = RTypeEvent::ROOMSELECTSTATE;
	      break;
	    case RTypeEvent::SETTINGS:
	      std::cout << "Settings button pressed" << std::endl;
	      break;
	    case RTypeEvent::SCORES:
	      std::cout << "Scores button pressed" << std::endl;
	      break;
	    case RTypeEvent::CREDITS:
	      std::cout << "Credits button pressed" << std::endl;
	      break;
	    case RTypeEvent::CREATE:
	      this->notify(RTypeEvent::CREATE);
	      _actualState = RTypeEvent::ROOMSTATE;
	      break;
	    case RTypeEvent::JOIN:
	      this->notify(RTypeEvent::JOIN);
	      _actualState = RTypeEvent::ROOMSTATE;
	      break;
	    case RTypeEvent::BACK:
	      this->prevState();
	      break;
	    case RTypeEvent::LISTCHOICE:
	      this->_editBoxRoomName->setText(this->_listRoom->getSelectedItem());
	    default:
	      break;
            }
         }
        window.clear();
        _stateToGui[_actualState]->draw();
        window.display();
    }
}

void	MenuView::stop()
{
  _run = false;
}

void MenuView::prevState()
{
  switch (_actualState)
    {
    case RTypeEvent::LOGINSTATE:
      break;
    case RTypeEvent::MENUSTATE:
      _actualState = RTypeEvent::LOGINSTATE;
      break;
    case RTypeEvent::ROOMSELECTSTATE:
      _actualState = RTypeEvent::MENUSTATE;
      break;
    case RTypeEvent::ROOMSTATE:
      _actualState = RTypeEvent::ROOMSELECTSTATE;
      break;
    default:
      break;
    }
}

void MenuView::setActualState(RTypeEvent::eMenuState state)
{
    _actualState = state;
}

RTypeEvent::eMenuState MenuView::getActualState() const
{
    return _actualState;
}

std::string MenuView::getLogin() const
{
    return std::string(_editBoxUsername->getText());
}

std::string MenuView::getRoomName() const
{
    return std::string(_editBoxRoomName->getText());
}

std::string MenuView::getRoomPass() const
{
    return std::string(_editBoxRoomPass->getText());
}

void MenuView::setRoomName(std::string name)
{
    this->_editBoxRoomName->setText(sf::String(name));
}

void MenuView::setPlayerLabe1(std::string name)
{
    this->_labelPlayer1->setText(sf::String(name));
}

void MenuView::setPlayerLabe2(std::string name)
{
    this->_labelPlayer2->setText(sf::String(name));
}

void MenuView::setPlayerLabe3(std::string name)
{
    this->_labelPlayer3->setText(sf::String(name));
}

void MenuView::setPlayerLabe4(std::string name)
{
    this->_labelPlayer4->setText(sf::String(name));
}
