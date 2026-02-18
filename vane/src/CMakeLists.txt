
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/gfxlib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/iolib")

add_library(vane_libs STATIC)
target_compile_features(
    vane_libs PUBLIC cxx_std_23
)
target_include_directories(
    vane_libs PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{VANE_THIRDPARTY_DIR}/include"
)
target_sources(
    vane_libs PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/util/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vanelog/vanelog.cpp"
)

target_link_libraries(
    vane_libs PUBLIC vane_gfxlib vane_iolib
)
