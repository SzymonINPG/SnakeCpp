#pragma once
#include "State.h"
#include "Game.h"

class StateFail :
    public State
{
public:
    StateFail(int STATE_ID, sf::RenderWindow& window, Font& font, Image& image);
    ~StateFail() override;
private:
    Text title;
    Text menuOptions[2];
    Texture backgroundTexture;
    Sprite backgroundImage;
    void titleInit();
    void menuOptionsInit();

public:
    virtual void init() override;
    virtual void update() override;
    virtual int handleEvents(Event&) override;
    virtual void render() override;
};

