add_library(vane_objects OBJECT)

target_sources(
    vane_objects PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform/platform_SDL2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/vanelog/vanelog.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/graphics.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/world.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mouse.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/service.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/window.cpp"
)


add_executable(vpart "${CMAKE_CURRENT_SOURCE_DIR}/vpart.cpp")
add_executable(vpkg "${CMAKE_CURRENT_SOURCE_DIR}/vpkg.cpp")
add_executable(vukg "${CMAKE_CURRENT_SOURCE_DIR}/vukg.cpp")
target_link_libraries(vpart PUBLIC vane_common)
target_link_libraries(vpkg PUBLIC vane_common)
target_link_libraries(vukg PUBLIC vane_common)
install(TARGETS vpart vpkg vukg RUNTIME DESTINATION "bin")



add_executable(tccdemo "${CMAKE_SOURCE_DIR}/src/tccdemo.cpp")
target_link_libraries(tccdemo PUBLIC tcc)
target_include_directories(tccdemo PUBLIC ${VANE_EXTERN_INCLUDE_DIR})
install(TARGETS tccdemo RUNTIME DESTINATION "bin")

