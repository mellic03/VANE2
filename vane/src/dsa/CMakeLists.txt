find_package(SDL3 REQUIRED)

add_library(vane_dsalib OBJECT)
target_compile_features(
    vane_dsalib PUBLIC cxx_std_23
)
target_include_directories(
    vane_dsalib PRIVATE ${VANE_INCLUDE_DIR}
)
target_sources(
    vane_dsalib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/bump_allocator.cpp"
)
