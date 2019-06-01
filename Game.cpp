#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>




Game::Game()
    :actualStateID(END)
{
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(SCRN_WIDTH, SCRN_HEIGHT), "Snake Project", Style::Close, settings);
    window.setFramerateLimit(60);
    window.clear();
    window.display();

 if (!font.loadFromFile("C:/Projekty/SnakeGameCpp/MySnake/Pliki/font2.ttf"))
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
            Image screenShot = window.capture();
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
