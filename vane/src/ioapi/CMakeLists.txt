
add_library(vane_ioapi OBJECT)
target_compile_features(
    vane_ioapi PUBLIC cxx_std_23
)
target_include_directories(
    vane_ioapi PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/h"
)
target_sources(
    vane_ioapi PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/ioapi.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/window.cpp"
)

target_link_libraries(
    vane_ioapi PUBLIC SDL3::SDL3
)
