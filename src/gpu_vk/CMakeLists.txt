
# set(VK_SDK_VERSION "1.4.341.1")
# set(VK_SDK_ARCH "x86_64")
# set(VK_SDK_DIR "${CMAKE_SOURCE_DIR}/external/vulkan/${VK_SDK_VERSION}/${VK_SDK_ARCH}")
set(ENV{VULKAN_SDK} "${CMAKE_SOURCE_DIR}/external/vulkan/1.4.341.1/x86_64")

find_package(SDL3 REQUIRED)
find_package(Vulkan REQUIRED)
find_package(slang REQUIRED CONFIG HINTS "$ENV{VULKAN_SDK}/lib/cmake")


add_library(vane_gpulib_vk STATIC)
target_compile_features(
    vane_gpulib_vk PUBLIC cxx_std_23
)
target_link_libraries(
    vane_gpulib_vk PUBLIC SDL3::SDL3 Vulkan::Vulkan
)
target_include_directories(
    vane_gpulib_vk PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${Vulkan_INCLUDE_DIRS}
)
target_sources(
    vane_gpulib_vk PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/platform.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp"
)


