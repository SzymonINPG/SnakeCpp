#include "StatePlay.h"
#include <ctime>
#include <cstdlib>


StatePlay::StatePlay(int STATE_ID, RenderWindow& window, Font& font)
    :State(STATE_ID, window, font),
    endgame(false),
    drawSnake(true),
    changeToFailScreen(false),
    colorAlpha(0) {}



StatePlay::~StatePlay()
{
    delete _snake;
    delete _food;
    music.stop();

}

Vector2f StatePlay::getRandomPosition()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Vector2i max(Game::SCREEN_WIDTH / Game::BLOCK_SIZE, Game::SCREEN_HEIGHT / Game::BLOCK_SIZE);
    Vector2f randomPosition;

    do
    {
        randomPosition = Vector2f(float(rand() % max.x), float(rand() % max.y));
    } while (_snake->contains(randomPosition*static_cast<float>(Game::BLOCK_SIZE)));

    return randomPosition;
}

void StatePlay::setBackground()
{

    for (int j = 0; j < Game::SCREEN_WIDTH / Game::BLOCK_SIZE; j++)
        for (int i = 0; i < Game::SCREEN_HEIGHT / Game::BLOCK_SIZE; i++)
        {
            RectangleShape square;
            square.setSize(Vector2f(static_cast<float>(Game::BLOCK_SIZE), static_cast<float>(Game::BLOCK_SIZE)));
            square.setFillColor(Color::Black);
            square.setOutlineThickness(-1.f);
            square.setOutlineColor(Color(55, 55, 55));
            square.setPosition(Vector2f(j*static_cast<float>(Game::BLOCK_SIZE), i*static_cast<float>(Game::BLOCK_SIZE)));
            fieldBoxes.push_back(square);
        }

}

void StatePlay::init()
{

    _snake = new Snake();

    _food = new RectangleShape();

    music.openFromFile(Game::path_to_file("music"));
    music.setLoop(true);
    music.setRelativeToListener(true);

    _food->setSize(Vector2f(static_cast<float>(Game::BLOCK_SIZE), static_cast<float>(Game::BLOCK_SIZE)));
    _food->setPosition(getRandomPosition() *static_cast<float>(Game::BLOCK_SIZE));
    _food->setFillColor(Color::Red);

    setBackground();
    fieldLines = FloatRect(0, 0, Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT);

    backgroundLayer.setPosition(Vector2f(0,0));
    backgroundLayer.setSize(Vector2f(Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT));
    backgroundLayer.setFillColor(Color(0, 0, 0, 0));

    music.setVolume(10.f);
    music.play();

    clock.restart();

}


void StatePlay::refresh()
{

    if (clock.getElapsedTime().asMilliseconds() > 125 && !endgame)
    {
        if (isFailHappening())
        {
            endgame = true;
            return;
        }

        _snake->Move();


        if (_snake->GetHeadFloatRect() == _food->getGlobalBounds())
        {
            _food->setPosition(getRandomPosition()*static_cast<float>(Game::BLOCK_SIZE));
            _snake->AddBodyPart();
        }

        clock.restart();

    }

    else if (endgame)
        handleFail();
}

bool StatePlay::isFailHappening()
{
    if (_snake->IsSelfBitting() || !fieldLines.contains(_snake->GetHeadPosition()))
        return true;

    return false;
}

void StatePlay::handleFail()
{
    music.setPitch(music.getPitch()*0.95f);
    music.setVolume(music.getVolume() *0.95f);

    if (!failAnimation())changeToFailScreen = true;

    colorAlpha+= 1.5f;

    backgroundLayer.setFillColor(Color(0, 0, 0, static_cast<unsigned char>(colorAlpha)));
}

int StatePlay::handleEvent(Event& event)
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
    if (changeToFailScreen)return Game::FAILURE;
    return STATE_ID;

}

void StatePlay::render()
{
    _window->clear();

    for (unsigned int i = 0; i <fieldBoxes.size(); i++)
        _window->draw(fieldBoxes[i]);

    _window->draw(*_food);

    if(drawSnake)_window->draw(*_snake);

    _window->draw(backgroundLayer);

    _window->display();
}

bool StatePlay::failAnimation()
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
