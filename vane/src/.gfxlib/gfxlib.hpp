#pragma once

#ifdef VANE_GFXLIB_CPU
    #include "gfxlib_cpu/platform_impl.hpp"

#elif defined(VANE_GFXLIB_GL)
    #include "gfxlib_gl/platform_impl.hpp"

#elif defined(VANE_GFXLIB_VK)
    #include "gfxlib_vk/platform_impl.hpp"

#else
    #error Must define VANE_GFXLIB_CPU, VANE_GFXLIB_GL or VANE_GFXLIB_VK

#endif

