find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "$ENV{THIRDPARTY_INSTALL_PREFIX}/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)


add_library(vane_gfx OBJECT)
target_compile_features(
    vane_gfx PUBLIC cxx_std_23
)
target_include_directories(
    vane_gfx PRIVATE
    "${VANE_INCPATH}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane_gfx PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/gl_validation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp"
)

