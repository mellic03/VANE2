
add_library(vane_libs STATIC)
target_compile_features(
    vane_libs PUBLIC cxx_std_23
)
target_include_directories(
    vane_libs PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{VANE_THIRDPARTY_DIR}/include"
)
target_sources(
    vane_libs PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/util/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vanelog/vanelog.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/io")


if(DEFINED VANE_GPULIB_GL)
    add_compile_definitions(VANE_GPULIB_GL)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gpu_gl")

elseif(DEFINED VANE_GPULIB_VK)
    add_compile_definitions(VANE_GPULIB_VK)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gpu_vk")
else()
    message(FATAL_ERROR "Must define VANE_GPULIB_GL or VANE_GPULIB_VK>")
endif()


target_link_libraries(
    vane_libs PUBLIC
    vane_iolib
    vane_gpulib
)
