
if(DEFINED VANE_GFXLIB_CPU)
    add_compile_definitions(VANE_GFXLIB_CPU)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gfxlib_cpu")

elseif(DEFINED VANE_GFXLIB_VK)
    add_compile_definitions(VANE_GFXLIB_VK)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gfxlib_vk")

elseif(DEFINED VANE_GFXLIB_GL)
    add_compile_definitions(VANE_GFXLIB_GL)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gfxlib_gl")

else()
    message(FATAL_ERROR "Must define VANE_GFXLIB_GL or VANE_GFXLIB_VK>")

endif()

