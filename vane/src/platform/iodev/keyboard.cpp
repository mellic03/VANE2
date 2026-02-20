#include "devices.hpp"
#include <cstring>


KeyboardIoDevice::KeyboardIoDevice(vane::Platform *plat)
:   vane::IoDevice(plat),
    mCurrDown(new bool[SDL_SCANCODE_COUNT]),
    mPrevDown(new bool[SDL_SCANCODE_COUNT])
{
    std::memset(mCurrDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
    std::memset(mPrevDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
}


void KeyboardIoDevice::update()
{
    memcpy(mPrevDown, mCurrDown, SDL_SCANCODE_COUNT*sizeof(bool));

    if (mTimer.hasExpired())
    {
        const bool *kbstate = SDL_GetKeyboardState(NULL);
        memcpy(mCurrDown, kbstate, SDL_SCANCODE_COUNT*sizeof(bool));
    }
}


bool KeyboardIoDevice::keyWasPressed(SDL_Scancode i)
{
    return !mPrevDown[i] && mCurrDown[i];
}

bool KeyboardIoDevice::keyWasReleased(SDL_Scancode i)
{
    return mPrevDown[i] && !mCurrDown[i];
}

bool KeyboardIoDevice::keyWasTapped(SDL_Scancode i)
{
    return i & false;
}

