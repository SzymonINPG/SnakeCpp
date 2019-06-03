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


        title.setString("Snake Na Projekt");
        title.setFont(*_font);
        title.setCharacterSize(86);
        title.setPosition(Vector2f(30, static_cast<float>(Game::BLOCK_SIZE / 2.f)));
        title.setFillColor(Color::Red);

}



void StateMenu::menuOptionsInit()
{
    const int howManyMenuOptions = 2;

    string menuOptionsStrings[howManyMenuOptions] = { "PLAY", "QUIT" };
    for (int i = 0; i < howManyMenuOptions; i++)
    {
        options[i].setString(menuOptionsStrings[i]);
        options[i].setFont(*_font);
        options[i].setCharacterSize(64);
        options[i].setFillColor(Color::White);
        options[i].setOrigin(Vector2f(options[i].getGlobalBounds().width / 2.f, options[i].getGlobalBounds().height / 2.f));
        options[i].setPosition(Vector2f(static_cast<float>(Game::SCREEN_WIDTH) / 2.f, static_cast<float>(Game::SCREEN_HEIGHT) / 2.f - 32.f + 2.5f*static_cast<float>(i)*32.f));
    }
}

int StateMenu::handleEvent(Event& event)
{
    Vector2f mousePosition = Vector2f(static_cast<float>(Mouse::getPosition(*_window).x), static_cast<float>(Mouse::getPosition(*_window).y));

    while (_window->pollEvent(event))
    {
        if (event.type == Event::Closed || (event.type == Event::MouseButtonReleased && options[1].getGlobalBounds().contains(mousePosition)))
            return Game::END;

        else if (event.type == Event::MouseButtonReleased && options[0].getGlobalBounds().contains(mousePosition))
            return Game::PLAY;
    }

    return STATE_ID;
}

void StateMenu::refresh()
{
    Vector2f mousePosition = Vector2f(static_cast<float>(Mouse::getPosition(*_window).x), static_cast<float>(Mouse::getPosition(*_window).y));

    for (int i = 0; i < 2; i++)
    {
        if (options[i].getGlobalBounds().contains(mousePosition))
        {
            options[i].setFillColor(Color::Cyan);
        }
        else options[i].setFillColor(Color::White);
    }
}

void StateMenu::render()
{
    _window->clear();

    _window->draw(title);

    for (int i = 0; i < 2; i++)
        _window->draw(options[i]);

    _window->display();

}
