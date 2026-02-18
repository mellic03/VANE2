#include "iolib.hpp"
#include <SDL3/SDL.h>
#include <cstring>
#include "../gfxlib/gfxlib.hpp"
#include "vane/log.hpp"

using namespace vane;


iolib::Keyboard::Keyboard(Platform *plat)
:   vane::IoDevice(plat, 500),
    mCurrDown(new bool[SDL_SCANCODE_COUNT]),
    mPrevDown(new bool[SDL_SCANCODE_COUNT])
{
    std::memset(mCurrDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
    std::memset(mPrevDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
}


void iolib::Keyboard::update()
{
    if (mTimer.hasExpired())
    {
        const bool *kbstate = SDL_GetKeyboardState(NULL);
        memcpy(mPrevDown, mCurrDown, SDL_SCANCODE_COUNT*sizeof(bool));
        memcpy(mCurrDown, kbstate, SDL_SCANCODE_COUNT*sizeof(bool));
    }

    else
    {
        memcpy(mPrevDown, mCurrDown, SDL_SCANCODE_COUNT*sizeof(bool));
    }
}


bool iolib::Keyboard::keyPressed(SDL_Scancode i)
{
    return !mPrevDown[i] && mCurrDown[i];
}


bool iolib::Keyboard::keyReleased(SDL_Scancode i)
{
    return mPrevDown[i] && !mCurrDown[i];
}


bool iolib::Keyboard::keyTapped(SDL_Scancode i)
{
    return i & false;
}

