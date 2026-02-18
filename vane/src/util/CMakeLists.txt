find_package(SDL3 REQUIRED)

add_library(vane_utillib OBJECT)
target_compile_features(
    vane_utillib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_utillib PUBLIC SDL3::SDL3
)
target_include_directories(
    vane_utillib PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{VANE_THIRDPARTY_DIR}/include"
)
target_sources(
    vane_utillib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/timer.cpp"
)
