#pragma once
#include "State.h"
#include "Game.h"

class StateMenu :
    public State
{
public:
    StateMenu(int STATE_ID, sf::RenderWindow& window, Font& font);
    ~StateMenu() override;

private:
    Text title;
    Text menuOptions[2];

    void TextInit();
    void menuOptionsInit();

public:
    virtual void init() override;
    virtual void update() override;
    virtual int handleEvents(Event&) override;
    virtual void render() override;
};



