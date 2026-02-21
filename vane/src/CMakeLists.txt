

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/dsa")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/game")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gfxlib/${VANE_GFXLIB_NAME}")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/platform/${VANE_PLATFORM_NAME}")

add_library(vane STATIC)
target_compile_features(
    vane PUBLIC cxx_std_23
)
target_include_directories(
    vane PRIVATE
    "${VANE_INCPATH}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/message.cpp"
)
target_link_libraries(
    vane PUBLIC
    vane_dsalib
    vane_gamelib
    vane_gfxlib
    vane_platformlib
)
