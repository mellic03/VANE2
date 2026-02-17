
find_package(OpenGL REQUIRED)

add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/lib/libglad.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/external/include"
)



target_sources(
    vane_gpu_libs PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
)
target_compile_features(
    vane_gpu_libs PUBLIC cxx_std_23
)
target_link_libraries(
    vane_gpu_libs PUBLIC glad OpenGL::GL OpenGL::GLU
)

