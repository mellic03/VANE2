
add_library(vane_libs STATIC)
target_compile_features(
    vane_libs PUBLIC cxx_std_23
)
target_include_directories(
    vane_libs PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/include"
)
target_sources(
    vane_libs PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/util/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vanelog/vanelog.cpp"
)


if(DEFINED VANE_GPULIB_GL)
    add_compile_definitions(VANE_GPULIB_GL)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gpu_gl")
    target_link_libraries(vane_libs PUBLIC vane_gpulib_gl)

elseif(DEFINED VANE_GPULIB_VK)
    add_compile_definitions(VANE_GPULIB_VK)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gpu_vk")
    target_link_libraries(vane_libs PUBLIC vane_gpulib_vk)
else()
    message(FATAL_ERROR "Must define VANE_GPULIB_GL or VANE_GPULIB_VK>")
endif()

