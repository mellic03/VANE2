
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
    "${CMAKE_CURRENT_SOURCE_DIR}/gfxapi_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/debugmsg.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/texture.cpp"
)
target_link_libraries(
    vane_gfxapi PUBLIC OpenGL::GL OpenGL::GLU vane_core
)

