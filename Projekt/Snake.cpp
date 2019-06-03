#include "Snake.h"
#include "Game.h"
#include <iostream>



using namespace sf;

Snake::Snake() : hasDirectionChanged(false)
{
    RectangleShape head;

    head.setFillColor(Color(10,200, 10, 100));
    head.setSize(Vector2f(static_cast<float>(Game::BLOCK_SIZE), static_cast<float>(Game::BLOCK_SIZE)));
    head.setPosition(Game::SCREEN_WIDTH/ 2, Game::SCREEN_HEIGHT / 2);
    head.setOutlineColor(Color(10,200, 100, 200));
    head.setOutlineThickness(-4);

    snakeParts.push_back(head);

    snakeDirection = DIR_UP;
}


Snake::~Snake()
{
}

Vector2f Snake::getDirection()
{
    Vector2f dir(0.f, 0.f);

    switch (snakeDirection)
    {
    case DIR_LEFT:
        dir.x = -1;
        break;

    case DIR_RIGHT:
        dir.x = 1;
        break;

    case DIR_UP:
        dir.y = -1;
        break;

    case DIR_DOWN:
        dir.y = 1;
        break;
    }
    hasDirectionChanged = false;
    return dir;
}

Vector2f Snake::getMovement()
{
    Vector2f direction = getDirection();
    Vector2f offset(direction.x * Game::BLOCK_SIZE, direction.y * Game::BLOCK_SIZE);
    return offset;
}

void Snake::Move()
{
    Vector2f prevPos = snakeParts[0].getPosition();
    snakeParts[0].move(getMovement());

    for (unsigned int i = 1; i < snakeParts.size(); i++)
    {
        Vector2f tmp = snakeParts[i].getPosition();
        snakeParts[i].setPosition(prevPos);
        prevPos = tmp;
    }
}


void Snake::ChangeDirection(Direction dir)
{
    if (std::abs(dir - snakeDirection) > 1 && !hasDirectionChanged)
    {
        snakeDirection = dir;
        hasDirectionChanged = true;
    }
}


void Snake::AddBodyPart()
{
    RectangleShape bodyPart(Vector2f(static_cast<float>(Game::BLOCK_SIZE), static_cast<float>(Game::BLOCK_SIZE)));

    bodyPart.setFillColor(Color(10,200, 10, 200));
    bodyPart.setSize(Vector2f(static_cast<float>(Game::BLOCK_SIZE), static_cast<float>(Game::BLOCK_SIZE)));
    bodyPart.setPosition(-32, -32);
    bodyPart.setOutlineColor(Color(10,200, 100, 200));
    bodyPart.setOutlineThickness(-4);
    snakeParts.push_back(bodyPart);
}

bool Snake::IsSelfBitting()
{
    const Vector2f headPositionAfterMovement = snakeParts[0].getPosition() + getMovement();
    const Vector2f* bodyPart;
    for (unsigned int i = 1; i < snakeParts.size(); i++)
    {
        bodyPart = &snakeParts[i].getPosition();
        if (headPositionAfterMovement == *bodyPart)
        {
            return true;
        }
    }

    return false;
}

FloatRect Snake::GetHeadFloatRect() const
{
    return snakeParts[0].getGlobalBounds();
}

bool Snake::contains(const Vector2f& position)
{
    for (unsigned int i = 0; i < snakeParts.size(); i++)
    {
        if (snakeParts[i].getPosition() == position)
        {
            return true;
        }
    }
    return false;
}


void Snake::draw(RenderTarget & target, RenderStates)  const
{
    for (unsigned int i = 0; i < snakeParts.size(); i++)
    {
        target.draw(snakeParts[i]);
    }
}

Vector2f Snake::GetHeadPosition()
{
    return snakeParts[0].getPosition() + getMovement();
}


