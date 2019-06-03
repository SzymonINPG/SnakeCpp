#include "StatePlay.h"
#include <ctime>
#include <cstdlib>


StatePlay::StatePlay(int STATE_ID, RenderWindow& window, Font& font)
    :State(STATE_ID, window, font),
    endOfGame(false),
    drawSnake(true),
    switchToFailureScreen(false),
    alphaColorChannel(0) {}



StatePlay::~StatePlay()
{
    delete _snake;
    delete _apple;
    music.stop();

}

Vector2f StatePlay::getRandomPosition()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Vector2i max(Game::SCRN_WIDTH / Game::APPLE_SIZE, Game::SCRN_HEIGHT / Game::APPLE_SIZE);
    Vector2f randomPosition;

    do
    {
        randomPosition = Vector2f(float(rand() % max.x), float(rand() % max.y));
    } while (_snake->contains(randomPosition*static_cast<float>(Game::APPLE_SIZE)));

    return randomPosition;
}

void StatePlay::setBackground()
{

    for (int j = 0; j < Game::SCRN_WIDTH / Game::APPLE_SIZE; j++)
        for (int i = 0; i < Game::SCRN_HEIGHT / Game::APPLE_SIZE; i++)
        {
            RectangleShape square;
            square.setSize(Vector2f(static_cast<float>(Game::APPLE_SIZE), static_cast<float>(Game::APPLE_SIZE)));
            square.setFillColor(Color::Black);
            square.setOutlineThickness(-1.f);
            square.setOutlineColor(Color(55, 55, 55));
            square.setPosition(Vector2f(j*static_cast<float>(Game::APPLE_SIZE), i*static_cast<float>(Game::APPLE_SIZE)));
            mapTiles.push_back(square);
        }

}

void StatePlay::init()
{

    _snake = new Snake();

    _apple = new RectangleShape();

    music.openFromFile(Game::path_to_file("music"));
    music.setLoop(true);
    music.setRelativeToListener(true);

    _apple->setSize(Vector2f(static_cast<float>(Game::APPLE_SIZE), static_cast<float>(Game::APPLE_SIZE)));
    _apple->setPosition(getRandomPosition() *static_cast<float>(Game::APPLE_SIZE));
    _apple->setFillColor(Color::Red);

    setBackground();
    mapBounds = FloatRect(0, 0, Game::SCRN_WIDTH, Game::SCRN_HEIGHT);

    transparentBackgroundLayer.setPosition(Vector2f(0,0));
    transparentBackgroundLayer.setSize(Vector2f(Game::SCRN_WIDTH, Game::SCRN_HEIGHT));
    transparentBackgroundLayer.setFillColor(Color(0, 0, 0, 0));

    music.setVolume(10.f);
    music.play();

    clock.restart();

}


void StatePlay::update()
{

    if (clock.getElapsedTime().asMilliseconds() > 125 && !endOfGame)
    {
        if (doesFailureOccurs())
        {
            endOfGame = true;
            return;
        }

        _snake->Move();


        if (_snake->GetHeadFloatRect() == _apple->getGlobalBounds())
        {
            _apple->setPosition(getRandomPosition()*static_cast<float>(Game::APPLE_SIZE));
            _snake->AddBodyPart();
        }

        clock.restart();

    }

    else if (endOfGame)
        handleFailure();
}

bool StatePlay::doesFailureOccurs()
{
    if (_snake->IsSelfBitting() || !mapBounds.contains(_snake->GetHeadPosition()))
        return true;

    return false;
}

void StatePlay::handleFailure()
{
    music.setPitch(music.getPitch()*0.95f);
    music.setVolume(music.getVolume() *0.95f);

    if (!playFailureAnimation())switchToFailureScreen = true;

    alphaColorChannel+= 1.5f;

    transparentBackgroundLayer.setFillColor(Color(0, 0, 0, static_cast<unsigned char>(alphaColorChannel)));
}

int StatePlay::handleEvents(Event& event)
{

    while (_window->pollEvent(event))
    {
        if (event.type == Event::Closed)
            return Game::END;

        else if (event.type == Event::KeyPressed)
        {

            switch (event.key.code)
            {
            case Keyboard::Left:
                _snake->ChangeDirection(Snake::DIR_LEFT);
                break;

            case Keyboard::Right:
                _snake->ChangeDirection(Snake::DIR_RIGHT);
                break;

            case Keyboard::Up:
                _snake->ChangeDirection(Snake::DIR_UP);
                break;

            case Keyboard::Down:
                _snake->ChangeDirection(Snake::DIR_DOWN);
                break;

            default:
                break;
            }
        }

    }
    if (switchToFailureScreen)return Game::FAILURE;
    return STATE_ID;

}

void StatePlay::render()
{
    _window->clear();

    for (unsigned int i = 0; i <mapTiles.size(); i++)
        _window->draw(mapTiles[i]);

    _window->draw(*_apple);

    if(drawSnake)_window->draw(*_snake);

    _window->draw(transparentBackgroundLayer);

    _window->display();
}

bool StatePlay::playFailureAnimation()
{
    static int animationCounter;

    if (clock.getElapsedTime().asSeconds() > 0.3f && drawSnake)
    {
        drawSnake = false;
        clock.restart();
    }
    else if (clock.getElapsedTime().asSeconds() > 0.2f && !drawSnake)
    {
        drawSnake = true;
        animationCounter++;
        clock.restart();
    }

    if (animationCounter >= 3)
    {
        animationCounter = 0;
        return false;
    }
    return true;
}
