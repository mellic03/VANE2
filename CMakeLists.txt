cmake_minimum_required(VERSION 3.5)

project(vaneprojects)

set(VANE_SRCPATH "${CMAKE_SOURCE_DIR}/vane/src")
set(VANE_INCPATH "${CMAKE_SOURCE_DIR}/vane/inc")
set(THIRDPARTY_PREFIX  "${CMAKE_SOURCE_DIR}/external/install/")
set(THIRDPARTY_INCPATH "${THIRDPARTY_PREFIX}/include")

include_directories("${VANE_SRCPATH}/platform")

add_subdirectory(vane)
add_subdirectory(vanetest)


