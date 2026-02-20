#pragma once

#include "vane/platform.hpp"
#include "vane/timer.hpp"

#include <SDL3/SDL.h>
#include <glm/glm.hpp>


class KeyboardIoDevice: public vane::IoDevice
{
public:
    KeyboardIoDevice(vane::Platform*);
    virtual void update() final;
    virtual void updateEvent(const SDL_Event&) final {  };
    bool keyWasPressed(SDL_Scancode);
    bool keyWasReleased(SDL_Scancode);
    bool keyWasTapped(SDL_Scancode);

private:
    vane::MsTimer mTimer;
    bool *mCurrDown;
    bool *mPrevDown;
};



class MouseIoDevice: public vane::IoDevice
{
public:
    enum class Button: int {
        NONE, LEFT, MID, RIGHT, EXTRA1, EXTRA2, NUM_BUTTONS
    };

    MouseIoDevice(vane::Platform*);
    virtual void update() final;
    virtual void updateEvent(const SDL_Event&) final;

    glm::vec2 mousePos();
    glm::vec2 mouseDelta();
    bool mouseWasPressed(Button, int clicks=0);
    bool mouseWasReleased(Button, int clicks=0);
    bool mouseWasClicked(Button, int n);

private:
    glm::vec2 mPos, mDPos, mDWheel;
    bool mCurrDown[int(Button::NUM_BUTTONS)];
    bool mPrevDown[int(Button::NUM_BUTTONS)];
    int  mClicks[int(Button::NUM_BUTTONS)];
};

