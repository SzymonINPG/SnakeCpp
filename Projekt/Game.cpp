#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>


#include <stdio.h>
#include <unistd.h>
#include <string>




Game::Game()
    :actualStateID(END)
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Snake Project", Style::Close, settings);
    window.setFramerateLimit(60);
    window.clear();
    window.display();


 if (!font.loadFromFile(Game::path_to_file("fond")))
   {
       std::cout << "Nie moge znalezc czcionki!"<< std::endl;
        return;
    }

    actualStateID=MENU;
}


Game::~Game()
{
}

void Game::runGame()
{
    actualState = new StateMenu(MENU, window, font);
    actualState->init();

    while (actualStateID != END)
    {
        if (actualStateID != actualState->getSTATE_ID())
            changeState();

        handleState();
    }
    window.close();
}

string Game::path_to_file(string type)
{
    char the_path[256];
    getcwd(the_path, 255);
    string str_path(the_path);
    size_t last_slash = 0;
    for(unsigned int i= 0 ; i<str_path.length(); i++)
    {
     if(str_path[i]=='\\')
     {
         str_path[i]='/';
         last_slash = i;
     }
    }
    str_path.resize(last_slash+1,'-');
    if(type=="fond")
    {
    str_path +="SnakeCpp-Test/Pliki/font2.ttf";
    }
    else if (type == "music")
    {
    str_path +="SnakeCpp-Test/Pliki/FreeKO_Fame.ogg";
    }
    return str_path;
}





void Game::changeState()
{
    delete actualState;

    switch (actualStateID)
    {
        case MENU:
            actualState = new StateMenu(MENU, window, font);
            break;
        case PLAY_STATE:
            actualState = new StatePlay(PLAY_STATE, window, font);
            break;
        case FAILURE:
            Texture texture;
            texture.create(SCRN_WIDTH,SCRN_HEIGHT);
            texture.update(window);
            Image screenShot = texture.copyToImage();
            actualState = new StateFail(FAILURE, window, font, screenShot);
            break;
    }

    actualState->init();
}

void Game::handleState()
{
    actualStateID = actualState->handleEvents(event);
    actualState->update();
    actualState->render();
}
