find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "$ENV{THIRDPARTY_INSTALL_PREFIX}/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)

add_library(vane_gfxlib STATIC)
target_compile_features(
    vane_gfxlib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_gfxlib PUBLIC SDL3::SDL3 glad OpenGL::GL OpenGL::GLU
)
target_include_directories(
    vane_gfxlib PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane_gfxlib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/window_impl.cpp"
)

