cmake_minimum_required(VERSION 3.28)

project(vanetest CXX)

set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

set(VANE_SRCPATH "$ENV{VANE_SRCPATH}")
set(VANE_INCPATH "$ENV{VANE_INCPATH}")

if(NOT DEFINED VANE_PLATFORM_NAME)
    message(FATAL_ERROR "Must define VANE_PLATFORM_NAME <sdl3|sfml|...>")
endif()

if(NOT DEFINED VANE_GFXLIB_NAME)
    message(FATAL_ERROR "Must define VANE_GFXLIB_NAME <cpu|gl|vk|...>")
endif()

include_directories("${VANE_SRCPATH}/platform/${VANE_PLATFORM_NAME}/h")
add_subdirectory("${VANE_SRCPATH}/dsa")
add_subdirectory("${VANE_SRCPATH}/game")
add_subdirectory("${VANE_SRCPATH}/platform/${VANE_PLATFORM_NAME}")



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






add_subdirectory("${CMAKE_SOURCE_DIR}/vane")

add_executable(
    ${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/vane/test/main.cpp"
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${VANE_INCLUDE_DIR}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC vane
)

