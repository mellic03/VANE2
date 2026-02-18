#include "iolib.hpp"
#include <cstring>

using namespace vane;


iolib::Keyboard::Keyboard(Platform *plat)
:   vane::IoDevice(plat, 1000),
    mCurrDown(new bool[SDL_SCANCODE_COUNT]),
    mPrevDown(new bool[SDL_SCANCODE_COUNT])
{
    std::memset(mCurrDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
    std::memset(mPrevDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
}

void iolib::Keyboard::update()
{
    memcpy(mPrevDown, mCurrDown, SDL_SCANCODE_COUNT*sizeof(bool));

    if (mTimer.hasExpired())
    {
        const bool *kbstate = SDL_GetKeyboardState(NULL);
        memcpy(mCurrDown, kbstate, SDL_SCANCODE_COUNT*sizeof(bool));
    }
}

bool iolib::Keyboard::keyWasPressed(SDL_Scancode i)
{
    return !mPrevDown[i] && mCurrDown[i];
}

bool iolib::Keyboard::keyWasReleased(SDL_Scancode i)
{
    return mPrevDown[i] && !mCurrDown[i];
}

bool iolib::Keyboard::keyWasTapped(SDL_Scancode i)
{
    return i & false;
}

