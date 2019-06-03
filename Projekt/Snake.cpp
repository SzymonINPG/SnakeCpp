#include "Snake.h"
#include "Game.h"
#include <iostream>



using namespace sf;

Snake::Snake() : hasDirectionChanged(false)
{
    RectangleShape head;

    head.setFillColor(Color(10,200, 10, 100));
    head.setSize(Vector2f(static_cast<float>(Game::APPLE_SIZE), static_cast<float>(Game::APPLE_SIZE)));
    head.setPosition(Game::SCRN_WIDTH/ 2, Game::SCRN_HEIGHT / 2);
    head.setOutlineColor(Color(10,200, 100, 200));
    head.setOutlineThickness(-4);
//    Texture texture;
//    texture.loadFromFile("C:/Projekty/SnakeGameCpp/MySnake/Pliki/body.png");
//    _apple->setTexture(&texture);


    m_snakeParts.push_back(head);

    m_direction = DIR_UP;
}


Snake::~Snake()
{
}

Vector2f Snake::getDirection()
{
    Vector2f dir(0.f, 0.f);

    switch (m_direction)
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
    Vector2f offset(direction.x * Game::APPLE_SIZE, direction.y * Game::APPLE_SIZE);
    return offset;
}

void Snake::Move()
{
    Vector2f prevPos = m_snakeParts[0].getPosition();
    m_snakeParts[0].move(getMovement());

    for (unsigned int i = 1; i < m_snakeParts.size(); i++)
    {
        Vector2f tmp = m_snakeParts[i].getPosition();
        m_snakeParts[i].setPosition(prevPos);
        prevPos = tmp;
    }
}


void Snake::ChangeDirection(Direction dir)
{
    if (std::abs(dir - m_direction) > 1 && !hasDirectionChanged)
    {
        m_direction = dir;
        hasDirectionChanged = true;
    }
}


void Snake::AddBodyPart()
{
    RectangleShape bodyPart(Vector2f(static_cast<float>(Game::APPLE_SIZE), static_cast<float>(Game::APPLE_SIZE)));

    bodyPart.setFillColor(Color(10,200, 10, 200));
    bodyPart.setSize(Vector2f(static_cast<float>(Game::APPLE_SIZE), static_cast<float>(Game::APPLE_SIZE)));
    bodyPart.setPosition(-32, -32);
    bodyPart.setOutlineColor(Color(10,200, 100, 200));
    bodyPart.setOutlineThickness(-4);
    m_snakeParts.push_back(bodyPart);
}

bool Snake::IsSelfBitting()
{
    const Vector2f headPositionAfterMovement = m_snakeParts[0].getPosition() + getMovement();
    const Vector2f* bodyPart;
    for (unsigned int i = 1; i < m_snakeParts.size(); i++)
    {
        bodyPart = &m_snakeParts[i].getPosition();
        if (headPositionAfterMovement == *bodyPart)
        {
            return true;
        }
    }

    return false;
}

FloatRect Snake::GetHeadFloatRect() const
{
    return m_snakeParts[0].getGlobalBounds();
}

bool Snake::contains(const Vector2f& position)
{
    for (unsigned int i = 0; i < m_snakeParts.size(); i++)
    {
        if (m_snakeParts[i].getPosition() == position)
        {
            return true;
        }
    }
    return false;
}


void Snake::draw(RenderTarget & target, RenderStates )  const
{
    for (unsigned int i = 0; i < m_snakeParts.size(); i++)
    {
        target.draw(m_snakeParts[i]);
    }
}

Vector2f Snake::GetHeadPosition()
{
    return m_snakeParts[0].getPosition() + getMovement();
}


