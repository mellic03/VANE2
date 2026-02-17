
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gpu")

find_package(SDL3 REQUIRED)

add_library(vane_platform STATIC)
target_include_directories(
    vane_platform PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${OPENGL_INCLUDE_DIR}"
)
target_sources(
    vane_platform PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform_SDL3.cpp"
)
target_compile_features(
    vane_platform PUBLIC cxx_std_23
)
target_link_libraries(
    vane_platform PUBLIC vane_gpu_libs SDL3::SDL3
)

