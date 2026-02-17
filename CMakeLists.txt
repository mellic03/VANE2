cmake_minimum_required(VERSION 3.21)


file(READ "${CMAKE_SOURCE_DIR}/version.txt" VANE_VERSION)
add_definitions(-DVANE_VERSION="${VANE_VERSION}")
message("${VANE_VERSION}")


project(vane)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/vane")

add_executable(
    ${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/src/main.cpp"
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include"
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC vane_libs
)

