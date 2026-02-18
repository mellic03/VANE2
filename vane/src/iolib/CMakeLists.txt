find_package(SDL3 REQUIRED)

add_library(vane_iolib OBJECT)
target_compile_features(
    vane_iolib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_iolib PUBLIC SDL3::SDL3
)
target_include_directories(
    vane_iolib PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane_iolib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/kb.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ms.cpp"
)
