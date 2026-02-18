#include "kb.hpp"
#include <SDL3/SDL.h>
#include <cstring>

using namespace vane;


iodev::Keyboard::Keyboard()
:   mCurrDown(new bool[SDL_SCANCODE_COUNT]),
    mPrevDown(new bool[SDL_SCANCODE_COUNT])
{
    std::memset(mCurrDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
    std::memset(mPrevDown, false, SDL_SCANCODE_COUNT*sizeof(bool));
}


void iodev::Keyboard::update(const SDL_Event &e)
{
    int idx = e.key.scancode;
    mPrevDown[idx] = mCurrDown[idx];
    mCurrDown[idx] = e.key.down;
}

bool iodev::Keyboard::keyPressed(SDL_Scancode i)
{
    return !mPrevDown[i] && mCurrDown[i];
}

bool iodev::Keyboard::keyReleased(SDL_Scancode i)
{
    return mPrevDown[i] && !mCurrDown[i];
}

bool iodev::Keyboard::keyTapped(SDL_Scancode i)
{
    return i & false;
}

