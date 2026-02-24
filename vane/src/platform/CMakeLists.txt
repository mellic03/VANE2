
add_library(vane_platform OBJECT)
target_compile_features(
    vane_platform PUBLIC cxx_std_23
)
target_include_directories(
    vane_platform PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/h"
)
target_sources(
    vane_platform PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ioapi.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/window.cpp"
)

target_link_libraries(
    vane_platform PUBLIC vane_gfxapi vane_ioapi
)
