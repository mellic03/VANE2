#pragma once

#include <cstdint>


namespace vane
{
    enum class message: uint64_t
    {
        SRV_NULL        = 0*256,
        SRV_STATUS,

        IO_NULL         = 1*256,
        IO_STATUS,
        IO_WIN_EVENT,
        IO_MOUSE_EVENT,
        IO_KEYUP_EVENT,
        IO_KEYDOWN_EVENT,

        GFX_NULL        = 2*256,
        GFX_STATUS,
        GFX_EVENT,
        GFX_EVENT_A,
        GFX_EVENT_B,
    };

    enum class command: int
    {
        SRV_NULL        = 0*256,
        SRV_ENABLE,
        SRV_DISABLE,
        SRV_RESTART,
        SRV_SHUTDOWN,

        IO_NULL         = 1*256,
        IO_KEY_ENABLE,
        IO_MOUSE_ENABLE,

        GFX_NULL        = 2*256,
        GFX_ENABLE,
        GFX_VSYNC_ENABLE,
        GFX_DISABLE,
        
    };
}
