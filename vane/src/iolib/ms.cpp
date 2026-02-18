#include "ms.hpp"
#include <SDL3/SDL.h>
#include <cstring>

using namespace vane;


iodev::Mouse::Mouse()
:   mPos(0), mDPos(0), mDWheel(0)
{
    memset(mCurrDown, 0, sizeof(mCurrDown));
    memset(mPrevDown, 0, sizeof(mPrevDown));
    memset(mClicks,   0, sizeof(mClicks));
}


void iodev::Mouse::update( const SDL_Event &e )
{
    int idx = e.button.button;

    switch (e.type)
    {
        default:
            // VANE_ASSERT(false, "Invalid type!");
            break;
        case SDL_EVENT_MOUSE_MOTION:
            SDL_GetMouseState(&mPos.x, &mPos.y);
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            mPrevDown[idx] = mCurrDown[idx];
            mCurrDown[idx] = true;
            mClicks[idx] = e.button.clicks;
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            mPrevDown[idx] = mCurrDown[idx];
            mCurrDown[idx] = false;
            mClicks[idx] = 0;
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            mDWheel.x += e.wheel.mouse_x;
            mDWheel.y += e.wheel.mouse_y;
            break;
    }
}

glm::vec2 iodev::Mouse::mousePos()
{
    return mPos;
}

glm::vec2 iodev::Mouse::mouseDelta()
{
    return mDPos;
}

bool iodev::Mouse::mousePressed( Button btn, int clicks )
{
    int i = int(btn);
    bool c = clicks>0 && clicks==mClicks[i];
    return c && !mPrevDown[i] && mCurrDown[i];
}

bool iodev::Mouse::mouseReleased( Button btn, int clicks )
{
    int i = int(btn);
    bool c = clicks>0 && clicks==mClicks[i];
    return c && mPrevDown[i] && !mCurrDown[i];
}

bool iodev::Mouse::mouseClicked( Button btn, int )
{
    int i = int(btn);
    return (!mPrevDown[i] && mCurrDown[i]) && false;
}


