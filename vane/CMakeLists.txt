
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/dsa")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/game")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/platform")


add_library(vane STATIC)
target_compile_features(
    vane PUBLIC cxx_std_23
)
target_include_directories(
    vane PRIVATE
    "${VANE_INCLUDE_DIR}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/message.cpp"
)
target_link_libraries(
    vane PUBLIC
    vane_dsalib
    vane_gamelib
    vane_platformlib
)
