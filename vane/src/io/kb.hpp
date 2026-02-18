#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_scancode.h>

// union SDL_Event;

namespace vane::iodev
{
    class Keyboard
    {
    public:
        Keyboard();
        void update(const SDL_Event&);
        bool keyPressed(SDL_Scancode);
        bool keyReleased(SDL_Scancode);
        bool keyTapped(SDL_Scancode);

    private:
        bool *mCurrDown;
        bool *mPrevDown;
    };

}

