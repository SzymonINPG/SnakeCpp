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
    RectangleShape* _apple;
    Clock clock;
    vector <RectangleShape> mapTiles;
    FloatRect mapBounds;
    Music music;
    RectangleShape transparentBackgroundLayer;
    Texture appleTexture;



    bool endOfGame;
    bool drawSnake;
    bool switchToFailureScreen;

    Vector2f getRandomPosition();
    void setBackground();

    bool playFailureAnimation();
    bool doesFailureOccurs();
    void handleFailure();
    float alphaColorChannel;
public:
    virtual void init() override;
    virtual void update() override;
    virtual int handleEvents(Event&) override;
    virtual void render() override;

};

