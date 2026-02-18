find_package(SDL3 REQUIRED)

add_library(vane_gamelib OBJECT)
target_compile_features(
    vane_gamelib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_gamelib PUBLIC SDL3::SDL3
)
target_include_directories(
    vane_gamelib PRIVATE
    $ENV{VANE_INCLUDE_DIR}
    $ENV{THIRDPARTY_INSTALL_PREFIX}/include
)
target_sources(
    vane_gamelib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/object.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/event.cpp"
)
