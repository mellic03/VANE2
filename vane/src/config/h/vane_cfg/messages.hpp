#pragma once


namespace vane
{
    struct msg
    {
        enum { BASE_ = 0, };

        struct ioapi { enum
        {
            BASE_ = vane::msg::BASE_,
            END_
        };};

        struct gfxapi { enum
        {
            BASE_ = vane::msg::ioapi::END_,
            WIN_EVENT,
            MAXIMIZE,
            MINIMIZE,
            KEY_UP,
            KEY_DOWN,
            END_
        };};

        enum { END_ = vane::msg::gfxapi::END_ };
    };


    struct cmd
    {
        enum { BASE_ = vane::msg::END_, };
        // PAUSE,
        // RESUME,
        // SHUTDOWN,

        struct ioapi { enum
        {
            BASE_ = vane::cmd::BASE_,
            END_
        };};

        struct gfxapi { enum
        {
            BASE_ = vane::cmd::ioapi::END_,
            WIN_MAXIMIZE,
            WIN_MINIMIZE,
            END_
        };};

        enum { END_ = vane::cmd::gfxapi::END_ };
    };

}
