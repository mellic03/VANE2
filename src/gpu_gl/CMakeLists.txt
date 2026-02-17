find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)
add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/include"
)

add_library(vane_gpulib_gl STATIC)
target_compile_features(
    vane_gpulib_gl PUBLIC cxx_std_23
)
target_link_libraries(
    vane_gpulib_gl PUBLIC SDL3::SDL3 glad OpenGL::GL OpenGL::GLU
)
target_include_directories(
    vane_gpulib_gl PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/include"
)
target_sources(
    vane_gpulib_gl PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp"
)

