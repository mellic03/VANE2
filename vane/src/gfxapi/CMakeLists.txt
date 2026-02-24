
add_library(vane_gfxapi OBJECT)
target_compile_features(
    vane_gfxapi PUBLIC cxx_std_23
)
target_include_directories(
    vane_gfxapi
    PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/h"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/h_"
    PRIVATE "${THIRDPARTY_PREFIX}/include"
)
target_sources(
    vane_gfxapi PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/resource/framebuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/resource/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/resource/texture.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gfx_api.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gfx_apictl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/underlyingtype.cpp"
)
target_link_libraries(
    vane_gfxapi PUBLIC OpenGL::GL OpenGL::GLU vane_core
)

