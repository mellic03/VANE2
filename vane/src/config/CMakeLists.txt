find_package(SDL3 REQUIRED)

add_library(vane_srvcfg INTERFACE)
target_include_directories(
    vane_srvcfg INTERFACE 
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(
    vane_srvcfg PUBLIC vane_core
)