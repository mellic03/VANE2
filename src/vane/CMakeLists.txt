
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/platform")


add_library(vane_libs STATIC)
target_include_directories(
    vane_libs PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/include"
)
target_sources(
    vane_libs PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/util/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vanelog/vanelog.cpp"
)
target_compile_features(
    vane_libs PUBLIC
    cxx_std_23
)
target_link_libraries(
    vane_libs PUBLIC
    vane_platform
)
