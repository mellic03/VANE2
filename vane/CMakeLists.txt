cmake_minimum_required(VERSION 3.28) # Essential for non-experimental module support

# file(READ "${CMAKE_SOURCE_DIR}/version.txt" VANE_VERSION)
# add_definitions(-DVANE_VERSION="${VANE_VERSION}")
# message("${VANE_VERSION}")

project(vane CXX)

if(DEFINED VANE_GFXLIB_CPU)
    add_compile_definitions(VANE_GFXLIB_CPU)
    add_subdirectory("$ENV{VANE_SOURCE_DIR}/gfxlib/gfxlib_cpu")
elseif(DEFINED VANE_GFXLIB_VK)
    add_compile_definitions(VANE_GFXLIB_VK)
    add_subdirectory("$ENV{VANE_SOURCE_DIR}/gfxlib/gfxlib_vk")
elseif(DEFINED VANE_GFXLIB_GL)
    add_compile_definitions(VANE_GFXLIB_GL)
    add_subdirectory("$ENV{VANE_SOURCE_DIR}/gfxlib/gfxlib_gl")
else()
    message(FATAL_ERROR "Must define VANE_GFXLIB_CPU, VANE_GFXLIB_GL or VANE_GFXLIB_VK>")
endif()

add_subdirectory("$ENV{VANE_SOURCE_DIR}/iolib")
add_subdirectory("$ENV{VANE_SOURCE_DIR}/util")

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
    ${PROJECT_NAME} PUBLIC
    vane_gfxlib
    vane_iolib
    vane_utillib
)

