find_package(SDL3 REQUIRED)

add_library(vane_dsa OBJECT)
target_compile_features(
    vane_dsa PUBLIC cxx_std_23
)
target_include_directories(
    vane_dsa
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/h"
    PUBLIC  "${THIRDPARTY_INCPATH}"
)
target_sources(
    vane_dsa PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/bump_allocator.cpp"
)
target_link_libraries(
    vane_dsa PUBLIC vane_core
)