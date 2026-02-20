cmake_minimum_required(VERSION 3.28)

project(vanetest CXX)

set(CMAKE_EXECUTABLE_SUFFIX_CXX ".elf")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/output)

set(VANE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vane/inc")
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

