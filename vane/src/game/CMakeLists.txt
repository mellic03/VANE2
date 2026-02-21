find_package(SDL3 REQUIRED)

add_library(vane_game OBJECT)
target_compile_features(
    vane_game PUBLIC cxx_std_23
)
target_include_directories(
    vane_game PRIVATE
    "${VANE_INCPATH}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane_game PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/component.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gamestate.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/world.cpp"
)