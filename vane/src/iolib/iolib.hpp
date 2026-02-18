#pragma once

#include "vane/iodev.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>
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
    // virtual void updateEvent(const SDL_Event&) final;
    bool keyPressed(SDL_Scancode);
    bool keyReleased(SDL_Scancode);
    bool keyTapped(SDL_Scancode);

private:
    bool *mCurrDown;
    bool *mPrevDown;
};



class vane::iolib::Mouse
{
public:
    enum class Button: int {
        NONE, LEFT, MID, RIGHT, EXTRA1, EXTRA2, NUM_BUTTONS
    };

    Mouse();
    void update(const SDL_Event&);
    glm::vec2 mousePos();
    glm::vec2 mouseDelta();
    bool mousePressed(Button, int clicks=0);
    bool mouseReleased(Button, int clicks=0);
    bool mouseClicked(Button, int n);

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