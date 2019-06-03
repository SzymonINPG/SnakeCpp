#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>


#include <stdio.h>
#include <unistd.h>
#include <string>




Game::Game()
    :currentStateID(END)
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake na Projekt", Style::Close, settings);
    window.setFramerateLimit(60);
    window.clear();
    window.display();


 if (!font.loadFromFile(Game::path_to_file("fond")))
   {
       std::cout << "Nie moge zaladowac czcionki!"<< std::endl;
        return;
    }

    currentStateID=MENU;
}


Game::~Game()
{
}

void Game::runGame()
{
    currentState = new StateMenu(MENU, window, font);
    currentState->init();

    while (currentStateID != END)
    {
        if (currentStateID != currentState->getSTATE_ID())
            changeState();

        handleState();
    }
    window.close();
}

//Poniewaz z niewiadomych powodow Qt Creator nie potrafil znajdywac sciezki do potrzebnych plikow, stworzylismy do tego odpowiednia funkcje :)

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
    str_path +="Projekt/Pliki/font2.ttf";
    }
    else if (type == "music")
    {
    str_path +="Projekt/Pliki/snake_4.ogg";
    }
    return str_path;
}





void Game::changeState()
{
    delete currentState;

    switch (currentStateID)
    {
        case MENU:
            currentState = new StateMenu(MENU, window, font);
            break;
        case PLAY:
            currentState = new StatePlay(PLAY, window, font);
            break;
        case FAILURE:
            Texture texture;
            texture.create(SCREEN_WIDTH,SCREEN_HEIGHT);
            texture.update(window);
            Image screenShot = texture.copyToImage();
            currentState = new StateFail(FAILURE, window, font, screenShot);
            break;
    }

    currentState->init();
}

void Game::handleState()
{
    currentStateID = currentState->handleEvent(event);
    currentState->refresh();
    currentState->render();
}
