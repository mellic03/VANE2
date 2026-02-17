add_library(vane_objects OBJECT)

target_include_directories(
    vane_objects PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/include"
)

target_sources(
    vane_objects PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/gl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform/platform_SDL3.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/util/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vanelog/vanelog.cpp"
    # "${CMAKE_CURRENT_SOURCE_DIR}/graphics.cpp"
    # "${CMAKE_CURRENT_SOURCE_DIR}/world.cpp"
)

target_compile_features(
    vane_objects PUBLIC
    cxx_std_23
)
