
add_library(vane_cfg OBJECT)
target_compile_features(
    vane_cfg PUBLIC cxx_std_23
)
target_include_directories(
    vane_cfg PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/h"
)
target_sources(
    vane_cfg PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/dummy.cpp"
)
