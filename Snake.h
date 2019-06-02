#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;


class Snake : public Drawable
{
public:


    Snake();
    ~Snake() override;

    enum Direction {
        DIR_UP, DIR_DOWN, DIR_LEFT = 3, DIR_RIGHT
    };

    FloatRect GetHeadFloatRect() const;
    Vector2f GetHeadPosition();

    void Move();
    void ChangeDirection(Direction dir);
    void AddBodyPart();
    bool IsSelfBitting();
    bool contains(const Vector2f& position);


    virtual void draw(sf::RenderTarget & target, sf::RenderStates ) const override;

private:
    std::vector <sf::RectangleShape> m_snakeParts;
    Direction m_direction;
    bool hasDirectionChanged;

    Vector2f getMovement();
    Vector2f getDirection();
};
