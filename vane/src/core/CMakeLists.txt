find_package(SDL3 REQUIRED)

add_library(vane_core OBJECT)
target_compile_features(
    vane_core PUBLIC cxx_std_23
)
target_include_directories(
    vane_core PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/h"
)
target_sources(
    vane_core PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/assert.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/objmanager.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/port.cpp"
)
