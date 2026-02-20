find_package(SDL3 REQUIRED)

add_library(vane_dsalib OBJECT)
target_compile_features(
    vane_dsalib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_dsalib PUBLIC SDL3::SDL3
)
target_include_directories(
    vane_dsalib PRIVATE "$ENV{VANE_INCLUDE_DIR}"
)
target_sources(
    vane_dsalib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/bump_allocator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/message.cpp"
)
