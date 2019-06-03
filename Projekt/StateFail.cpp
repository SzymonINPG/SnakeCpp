#include "StateFail.h"




StateFail::StateFail(int STATE_ID, RenderWindow& window, Font& font, Image& image)
    :State(STATE_ID,window,font)
{
    backgroundTexture.loadFromImage(image);
    backgroundImage.setTexture(backgroundTexture);
}


void StateFail::titleInit()
{
    title.setString("Game over!");
    title.setFont(*_font);
    title.setCharacterSize(86);
    title.setFillColor(Color::Cyan);
    title.setOrigin(Vector2f(title.getGlobalBounds().width / 2.f, title.getGlobalBounds().height / 2.f));
    title.setPosition(Vector2f(Game::SCREEN_WIDTH / 2.f, static_cast<float>(Game::BLOCK_SIZE)));
}

void StateFail::menuOptionsInit()
{
    const int howManyMenuOptions = 2;

    string menuOptionsStrings[howManyMenuOptions] = { "PLAY AGAIN", "MENU" };
    for (int i = 0; i < howManyMenuOptions; i++)
    {
        options[i].setString(menuOptionsStrings[i]);
        options[i].setFont(*_font);
        options[i].setCharacterSize(64);
        options[i].setFillColor(Color::White);
        options[i].setOrigin(Vector2f(options[i].getGlobalBounds().width / 2.f, options[i].getGlobalBounds().height / 2.f));
        options[i].setPosition(Vector2f(static_cast<float>(Game::SCREEN_WIDTH) / 2.f, static_cast<float>(Game::SCREEN_HEIGHT) / 2.f - static_cast<float>(Game::BLOCK_SIZE) + 2.5f* static_cast<float>(i)*static_cast<float>(Game::BLOCK_SIZE)));
    }
}

void StateFail::init()
{
    titleInit();
    menuOptionsInit();
}

void StateFail::refresh()
{
    Vector2f mousePosition = Vector2f(static_cast<float>(Mouse::getPosition(*_window).x), static_cast<float>(Mouse::getPosition(*_window).y));

    for (int i = 0; i < 2; i++)
    {
        if (options[i].getGlobalBounds().contains(mousePosition))
            options[i].setFillColor(sf::Color::Cyan);
        else options[i].setFillColor(sf::Color::White);
    }

}

void StateFail::render()
{
    _window->clear();

    _window->draw(backgroundImage);
    _window->draw(title);

    for (int i = 0; i < 2; i++)
        _window->draw(options[i]);

    _window->display();
}
int StateFail::handleEvent(Event& event)
{

    Vector2f mousePosition = Vector2f(static_cast<float>(Mouse::getPosition(*_window).x), static_cast<float>(Mouse::getPosition(*_window).y));

    while (_window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            return Game::END;

        else if (event.type == Event::MouseButtonReleased && options[0].getGlobalBounds().contains(mousePosition))
            return Game::PLAY;

        else if (event.type == Event::MouseButtonReleased && options[1].getGlobalBounds().contains(mousePosition))
            return Game::MENU;
    }

    return STATE_ID;
}

StateFail::~StateFail(){}
