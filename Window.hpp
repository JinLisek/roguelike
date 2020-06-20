#pragma once

#include <array>
#include <string>
#include <ncurses.h>
#include <unistd.h>
#include <cstdlib>

#include "PlayerCharacter.hpp"
#include "Tile.hpp"

class Window
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
        curs_set(0);
    }

    ~Window() {
        delwin(_windowHandle);
        endwin();
        refresh();
    }

    void redrawMap(const PlayerCharacter& pc, const std::array<std::array<Tile, 80>, 25>& map) {
        clear();
        drawMap(map);
        mvprintw(pc.posY, pc.posX, "@");
        refresh();
    }

private:
    void drawMap(const std::array<std::array<Tile, 80>, 25>& map) {
        for(std::size_t posY = 0; posY < 25; ++posY) {
            std::string mapRow {};
            for(std::size_t posX = 0; posX < 80; ++posX) {
                if (map[posY][posX] == Tile::Dirt)
                    mapRow += '.';
                if (map[posY][posX] == Tile::Wall)
                    mapRow += '#';
            }
            mvprintw(posY, 0, mapRow.c_str());
        }
    }

    WINDOW * _windowHandle;
    const int rows  = 25;
    const int cols   = 80;
    int x = 0;
    int y = 0;
};