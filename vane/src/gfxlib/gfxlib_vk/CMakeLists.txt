
# set(VK_SDK_VERSION "1.4.341.1")
# set(VK_SDK_ARCH "x86_64")
# set(VK_SDK_DIR "${CMAKE_SOURCE_DIR}/external/vulkan/${VK_SDK_VERSION}/${VK_SDK_ARCH}")
# set(ENV{VULKAN_SDK} "${CMAKE_SOURCE_DIR}/external/vulkan/1.4.341.1/x86_64")
# set(ENV{VULKAN_SDK} "${CMAKE_SOURCE_DIR}/external/vulkan/1.4.341.1/x86_64")
set(ENV{VULKAN_SDK} "${THIRDPARTY_INSTALL_PREFIX}")

find_package(SDL3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(slang REQUIRED CONFIG HINTS "$ENV{THIRDPARTY_INSTALL_PREFIX}")


add_library(vane_gfxlib STATIC)
target_compile_features(
    vane_gfxlib PUBLIC cxx_std_23
)
target_link_libraries(
    vane_gfxlib PUBLIC SDL3::SDL3 Vulkan::Vulkan
)
target_include_directories(
    vane_gfxlib PRIVATE
    "$ENV{VANE_INCLUDE_DIR}"
    "$ENV{VANE_THIRDPARTY_DIR}/include"
    ${Vulkan_INCLUDE_DIRS}
)
target_sources(
    vane_gfxlib PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform_impl.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
)

