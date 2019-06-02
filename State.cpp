#include "State.h"


State::State(int STATE_ID, sf::RenderWindow& window, Font& font)
    : _font(&font),_window(&window),STATE_ID(STATE_ID)
{

}

State::~State()
{

}

int State::getSTATE_ID() const
{
    return STATE_ID;
}


