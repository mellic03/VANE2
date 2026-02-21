find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "$ENV{THIRDPARTY_INSTALL_PREFIX}/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)

add_library(vane_platformlib OBJECT)
target_compile_features(
    vane_platformlib PUBLIC cxx_std_23
)
target_include_directories(
    vane_platformlib PRIVATE
    "${VANE_INCPATH}"
    "${VANE_INCPATH_P}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane_platformlib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gl_validation.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time.cpp"
)
target_link_libraries(
    vane_platformlib PRIVATE SDL3::SDL3 glad OpenGL::GL OpenGL::GLU
)
