
find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

# add_library(glad STATIC IMPORTED)
# set_target_properties(glad PROPERTIES
#     IMPORTED_LOCATION "${THIRDPARTY_PREFIX}/lib/libglad.a"
#     INTERFACE_INCLUDE_DIRECTORIES "${THIRDPARTY_PREFIX}/include"
# )
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/h")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/core")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/dsa")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/game")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/gfxapi")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/platform")

add_library(
    vane STATIC "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
)

target_link_libraries(
    vane PUBLIC
    vane_core
    vane_dsa
    vane_game
    vane_gfxapi
    vane_platform
)

