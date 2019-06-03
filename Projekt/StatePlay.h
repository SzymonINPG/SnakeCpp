#pragma once
#include "State.h"
#include "Snake.h"
#include "Game.h"
#include <SFML/Audio.hpp>


class StatePlay :
    public State
{
public:
    StatePlay(int STATE_ID, sf::RenderWindow& window, Font& font);
    ~StatePlay() override;

private:
    Snake* _snake;
    RectangleShape* _food;
    Clock clock;
    vector <RectangleShape> fieldBoxes;
    FloatRect fieldLines;
    Music music;
    RectangleShape backgroundLayer;

    bool endgame;
    bool drawSnake;
    bool changeToFailScreen;

    Vector2f getRandomPosition();
    void setBackground();

    bool failAnimation();
    bool isFailHappening();
    void handleFail();
    float colorAlpha;
public:
    virtual void init() override;
    virtual void refresh() override;
    virtual int handleEvent(Event&) override;
    virtual void render() override;

};

