#pragma once

#ifdef VANE_GPU_OPENGL
    #include "opengl/gl.hpp"
#elif defined(VANE_GPU_VULKAN)

#else
    #error Must define VANE_GPU_OPENGL or VANE_GPU_VULKAN
#endif

