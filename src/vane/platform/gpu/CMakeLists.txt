
add_library(vane_gpu_libs STATIC)
target_include_directories(
    vane_gpu_libs PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/include"
)

if(DEFINED VANE_GPU_OPENGL)
    message("VANE_GPU_OPENGL")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/opengl")
elseif(DEFINED VANE_GPU_VULKAN)
    message("VANE_GPU_VULKAN")
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vulkan")
else()
    message(FATAL_ERROR "Must define VANE_GPU_OPENGL or VANE_GPU_VULKAN>")
endif()
