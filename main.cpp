#include "KeyboardInputHandler.hpp"
#include "Window.hpp"
#include "PlayerController.hpp"

int main()
{
    Window gameWindow{};
    PlayerController playerController {gameWindow};
    KeyboardInputHandler{playerController}.loop();

    return EXIT_SUCCESS;
}