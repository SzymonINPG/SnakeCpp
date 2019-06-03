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
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 640;
    static const int BLOCK_SIZE = 32;
    enum {END, MENU, PLAY, FAILURE};
    static string path_to_file(string);
private:
    RenderWindow window;
    Font font;
    Event event;
    State * currentState;
    int currentStateID;
    void changeState();
    void handleState();


public:
    Game();
    ~Game();
    void runGame();


};

