#include "StateMenu.h"
#include <iostream>



StateMenu::StateMenu(int STATE_ID, RenderWindow& window, Font& font)
    :State(STATE_ID,window,font)
{
}


StateMenu::~StateMenu()
{
}

void StateMenu::init()
{
    TextInit();
    menuOptionsInit();
}

void StateMenu::TextInit()
{


        title.setString("SNAKE PROJECT");
        title.setFont(*_font);
        title.setCharacterSize(86);
        title.setPosition(Vector2f(350, static_cast<float>(Game::APPLE_SIZE / 2.f)));
        title.setFillColor(Color::Red);

}



void StateMenu::menuOptionsInit()
{
    const int howManyMenuOptions = 2;

    string menuOptionsStrings[howManyMenuOptions] = { "PLAY", "EXIT" };
    for (int i = 0; i < howManyMenuOptions; i++)
    {
        menuOptions[i].setString(menuOptionsStrings[i]);
        menuOptions[i].setFont(*_font);
        menuOptions[i].setCharacterSize(64);
        menuOptions[i].setFillColor(Color::White);
        menuOptions[i].setOrigin(Vector2f(menuOptions[i].getGlobalBounds().width / 2.f, menuOptions[i].getGlobalBounds().height / 2.f));
        menuOptions[i].setPosition(Vector2f(static_cast<float>(Game::SCRN_WIDTH) / 2.f, static_cast<float>(Game::SCRN_HEIGHT) / 2.f - 32.f + 2.5f*static_cast<float>(i)*32.f));
    }
}

int StateMenu::handleEvents(Event& event)
{
    Vector2f mousePosition = Vector2f(static_cast<float>(Mouse::getPosition(*_window).x), static_cast<float>(Mouse::getPosition(*_window).y));

    while (_window->pollEvent(event))
    {
        if (event.type == Event::Closed || (event.type == Event::MouseButtonReleased && menuOptions[1].getGlobalBounds().contains(mousePosition)))
            return Game::END;

        else if (event.type == Event::MouseButtonReleased && menuOptions[0].getGlobalBounds().contains(mousePosition))
            return Game::PLAY_STATE;
    }

    return STATE_ID;
}

void StateMenu::update()
{
    Vector2f mousePosition = Vector2f(static_cast<float>(Mouse::getPosition(*_window).x), static_cast<float>(Mouse::getPosition(*_window).y));

    for (int i = 0; i < 2; i++)
    {
        if (menuOptions[i].getGlobalBounds().contains(mousePosition))
        {
            menuOptions[i].setFillColor(Color::Cyan);
        }
        else menuOptions[i].setFillColor(Color::White);
    }
}

void StateMenu::render()
{
    _window->clear();

    _window->draw(title);

    for (int i = 0; i < 2; i++)
        _window->draw(menuOptions[i]);

    _window->display();

}
