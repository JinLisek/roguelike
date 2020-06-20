#include "KeyboardInputHandler.hpp"
#include "Window.hpp"

int main()
{
    Window gameWindow{};
    KeyboardInputHandler{gameWindow}.loop();

    return EXIT_SUCCESS;
}