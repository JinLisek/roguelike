#pragma once

#include <array>
#include <string>
#include <random>
#include "ncurses.h"

#include "IKeyboardInputObserver.hpp"
#include "PlayerCharacter.hpp"
#include "Window.hpp"
#include "Tile.hpp"

class GameController : public IKeyboardInputObserver {
public:
    GameController(Window& window) :
        percentage_distribution{0, 100},
        _window{window}
    {
        std::uint32_t rngSeed = 69;
        rngEngine.seed(rngSeed);
        _map = randomizeMap();
        _window.redrawMap(PlayerCharacter {0, 0}, _map);
    }

    void onKeyPressed(int ch) override {
        unsigned newY = y;
        unsigned newX = x;
        switch ( ch ) {

        case KEY_UP:
            --newY;
            break;

        case KEY_DOWN:
            ++newY;
            break;

        case KEY_LEFT:
            --newX;
            break;

        case KEY_RIGHT:
            ++newX;
            break;
        }

        if(newX >= 0 and newX < cols and newY >= 0 and newY < rows and _map[newY][newX] != Tile::Wall)
        {
            x = newX;
            y = newY;
        }


        _window.redrawMap(PlayerCharacter {x, y}, _map);
    }

private:
    std::mt19937 rngEngine;
    std::uniform_int_distribution<uint32_t> percentage_distribution;
    Window& _window;
    const unsigned rows  = 25;
    const unsigned cols   = 80;
    unsigned x = 0;
    unsigned y = 0;

    std::array<std::array<Tile, 80>, 25> randomizeMap()
    {
        std::array<std::array<Tile, 80>, 25> map;
        
        for(std::size_t posY = 0; posY < 25; ++posY) {
            for(std::size_t posX = 0; posX < 80; ++posX) {
                const auto randomPercentage = percentage_distribution(rngEngine);
                if(randomPercentage < 10)
                    map[posY][posX] = Tile::Wall;
                else
                    map[posY][posX] = Tile::Dirt;
            }
        }


        return map;
    }

    std::array<std::array<Tile, 80>, 25> _map;
};