cmake_minimum_required(VERSION 3.5)

project(vaneprojects VERSION 1.0.13.0)

set(VANE_SRCPATH "${CMAKE_SOURCE_DIR}/vane/src")
set(VANE_INCPATH "${CMAKE_SOURCE_DIR}/vane/inc")
set(THIRDPARTY_PREFIX  "${CMAKE_SOURCE_DIR}/external/install/")
set(THIRDPARTY_INCPATH "${THIRDPARTY_PREFIX}/include")

include_directories("${VANE_SRCPATH}/platform")

add_subdirectory(vane)
add_subdirectory(vanegame)

# configure_file(
#     "${PROJECT_SOURCE_DIR}/version.h.in"
#     "${PROJECT_BINARY_DIR}/version.h"
# )
