cmake_minimum_required(VERSION 3.28) # Essential for non-experimental module support

# file(READ "${CMAKE_SOURCE_DIR}/version.txt" VANE_VERSION)
# add_definitions(-DVANE_VERSION="${VANE_VERSION}")
# message("${VANE_VERSION}")

project(vane CXX)

add_subdirectory("$ENV{VANE_SOURCE_DIR}")

add_executable(
    ${PROJECT_NAME} "$ENV{VANE_SOURCE_DIR}/main.cpp"
)
target_include_directories(
    ${PROJECT_NAME} PUBLIC "$ENV{VANE_INCLUDE_DIR}"
)
target_compile_features(
    ${PROJECT_NAME} PUBLIC cxx_std_23
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC vane_libs
)

