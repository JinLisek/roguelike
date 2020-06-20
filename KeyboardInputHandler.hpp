#pragma once

#include <vector>
#include <ncurses.h>

#include "IKeyboardInputObserver.hpp"

class KeyboardInputHandler
{
public:
    KeyboardInputHandler(IKeyboardInputObserver& observer) :
        _registeredObserver(observer)
    {
    }

    void loop(){
        int ch;
        while ( (ch = getch()) != 'q' ) {
            _registeredObserver.onKeyPressed(ch);
        }
    }
    
private:
    IKeyboardInputObserver& _registeredObserver;
};