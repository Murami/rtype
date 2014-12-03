
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "MenuView.h"
#include "MenuController.h"

#define WIDTH   2880
#define HEIGHT  1800

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "TGUI window", sf::Style::Fullscreen);


    MenuView menuView(window);
    MenuController menuController(menuView);
    
    menuView.addObserver(&menuController);
    menuView.run(window);
}


