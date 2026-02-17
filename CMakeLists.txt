cmake_minimum_required(VERSION 3.21)

project(vane)

find_package(SDL2 REQUIRED)

include_directories("${CMAKE_SOURCE_DIR}/include/" "${VANE_EXTERN_INCLUDE_DIR}")
add_subdirectory("${CMAKE_SOURCE_DIR}/src/")

add_executable(
    ${PROJECT_NAME}
    "${CMAKE_SOURCE_DIR}/src/main.cpp")


target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}
    SDL2
)

