cmake_minimum_required(VERSION 3.21)

project(vane)


find_package(OpenGL REQUIRED)
find_package(SDL3 REQUIRED)

add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/include"
)


add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/vane")

add_executable(
    ${PROJECT_NAME}
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}/include"
)

target_compile_features(
    ${PROJECT_NAME} PUBLIC
    cxx_std_23
)

target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    glad
    OpenGL::GL
    vane_objects
    SDL3::SDL3
)

