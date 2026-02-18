#pragma once

#include "vane/iodev.hpp"
#include <SDL3/SDL.h>
#include <glm/glm.hpp>


namespace vane::iolib
{
    class Keyboard;
    class Mouse;
}


class vane::iolib::Keyboard: public vane::IoDevice
{
public:
    Keyboard(Platform*);
    virtual void update() final;
    virtual void updateEvent(const SDL_Event&) final {  };
    bool keyWasPressed(SDL_Scancode);
    bool keyWasReleased(SDL_Scancode);
    bool keyWasTapped(SDL_Scancode);

private:
    bool *mCurrDown;
    bool *mPrevDown;
};



class vane::iolib::Mouse: public vane::IoDevice
{
public:
    enum class Button: int {
        NONE, LEFT, MID, RIGHT, EXTRA1, EXTRA2, NUM_BUTTONS
    };

    Mouse(Platform*);
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

// struct MouseState
// {
//     bool l, m, r;
//     float x, y;
// };

// // struct MouseData
// // {
// //     bool left, mid, right;

// //     struct {
// //         int8_t left, mid, right;
// //     } dir;
    
// //     float x, y;
// // };