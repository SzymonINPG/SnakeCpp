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
    Text options[2];
    Texture backgroundTexture;
    Sprite backgroundImage;
    void titleInit();
    void menuOptionsInit();

public:
    virtual void init() override;
    virtual void refresh() override;
    virtual int handleEvent(Event&) override;
    virtual void render() override;
};

