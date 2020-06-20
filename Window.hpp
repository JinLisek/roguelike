#pragma once

#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>

#include "IKeyboardInputObserver.hpp"

class Window : public IKeyboardInputObserver
{
public:
    Window() {
        if ( (_windowHandle = initscr()) == nullptr ) {
            fprintf(stderr, "Error initialising ncurses.\n");
            exit(EXIT_FAILURE);
        }

        noecho();
        keypad(_windowHandle, TRUE);
        start_color();
    }

    ~Window() {
        delwin(_windowHandle);
        endwin();
        refresh();
    }

    void onKeyPressed(int ch) override {
        switch ( ch ) {

        case KEY_UP:
            if ( y > 0 )
            --y;
            break;

        case KEY_DOWN:
            if ( y < (rows - height) )
            ++y;
            break;

        case KEY_LEFT:
            if ( x > 0 )
            --x;
            break;

        case KEY_RIGHT:
            if ( x < (cols - width) )
            ++x;
            break;

        case KEY_HOME:
            x = 0;
            y = 0;
            break;

        case KEY_END:
            x = (cols - width);
            y = (rows - height);
            break;
        }
    
        clear();
        mvprintw(y, x, "@");
        refresh();
    }

private:
    WINDOW * _windowHandle;
    int width = 23;
    int height = 7;
    int rows  = 25;
    int cols   = 80;
    int x = (cols - width)  / 2;
    int y = (rows - height) / 2;
};