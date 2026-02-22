#pragma once

#define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_raii.hpp>


// static void vane_vk_test()
// {
//     vkContext context;
//     VkInstance instance;
//     VkInstanceCreateInfo createInfo{};

//     constexpr vk::ApplicationInfo appInfo{
//         .pApplicationName   = "Hello Triangle",
//         .applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
//         .pEngineName        = "No Engine",
//         .engineVersion      = VK_MAKE_VERSION( 1, 0, 0 ),
//         .apiVersion         = vk::ApiVersion14};

//     vk::InstanceCreateInfo createInfo{
//         .pApplicationInfo = &appInfo
//     };

//     // instance = vk::detail::raii::Instance(context, createInfo);
// }

