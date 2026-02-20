
add_library(vane STATIC)
target_compile_features(
    vane PUBLIC cxx_std_23
)
target_include_directories(
    vane PRIVATE
    "${CMAKE_SOURCE_DIR}/inc"
    "$ENV{THIRDPARTY_INSTALL_PREFIX}/include"
)
target_sources(
    vane PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/file.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/log.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/message.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/time.cpp"
)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/platform")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/iolib")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/util")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/dsa")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/src/game")

# target_link_libraries(
#     vane PUBLIC SDL3::SDL3
# )


