#pragma once

class IKeyboardInputObserver {
public:
    virtual ~IKeyboardInputObserver() = default;
    virtual void onKeyPressed(int keyCode) = 0;
};