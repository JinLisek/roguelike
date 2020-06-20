#include "KeyboardInputHandler.hpp"
#include "Window.hpp"
#include "GameController.hpp"

int main()
{
    Window gameWindow{};
    GameController gameController {gameWindow};
    KeyboardInputHandler{gameController}.loop();

    return EXIT_SUCCESS;
}