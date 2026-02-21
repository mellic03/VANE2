find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "$ENV{THIRDPARTY_INSTALL_PREFIX}/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)

add_library(vane_platform OBJECT)
target_compile_features(
    vane_platform PUBLIC cxx_std_23
)
target_include_directories(
    vane_platform PRIVATE
    "${VANE_INCPATH}"
    "${VANE_INCPATH_P}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane_platform PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time.cpp"
)

target_link_libraries(
    vane_platform PUBLIC vane_gfx
)
