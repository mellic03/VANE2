find_package(SDL3 REQUIRED)

add_library(vane_objectlib OBJECT)
target_compile_features(
    vane_objectlib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_objectlib PUBLIC SDL3::SDL3
)
target_include_directories(
    vane_objectlib PRIVATE
    $ENV{VANE_INCLUDE_DIR}
    $ENV{THIRDPARTY_INSTALL_PREFIX}/include
)
target_sources(
    vane_objectlib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/object.cpp"
)
