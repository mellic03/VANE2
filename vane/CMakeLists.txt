cmake_minimum_required(VERSION 3.28)

project(vane CXX)
add_subdirectory("${CMAKE_SOURCE_DIR}/src")


target_include_directories(
    ${PROJECT_NAME} PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    ${PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/src/file.cpp"
    "${CMAKE_SOURCE_DIR}/src/log.cpp"
)

add_subdirectory("${CMAKE_SOURCE_DIR}/src/platform")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/iolib")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/util")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/dsa")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/game")

target_link_libraries(
    ${PROJECT_NAME} PUBLIC SDL3::SDL3
)


