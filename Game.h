#pragma once
#include "State.h"
#include "StateMenu.h"
#include <windows.h>
#include "StatePlay.h"
#include <iostream>
#include "StateFail.h"


class Game
{
public:
    static const int SCRN_WIDTH = 1280;
    static const int SCRN_HEIGHT = 768;
    static const int APPLE_SIZE = 32;
    enum {END, MENU, PLAY_STATE, FAILURE};
private:
    RenderWindow window;
    Font font;
    Event event;
    State * actualState;
    int actualStateID;
    void changeState();
    void handleState();

public:
    Game();
    ~Game();
    void runGame();


};

