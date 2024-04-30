#pragma once

#include <vulkan\vulkan.h>

#include <vector>

#include "VulkanDebugMessenger.h"

class VulkanInstance
{

    VkInstance instance;

#ifdef _DEBUG
    VulkanDebugMessenger db_messenger;
#endif

    bool enableLayers;

	bool checkLayerSupport(const std::vector<const char*>& layers);

	bool checkInstanceExtensionSupport(const std::vector<const char*>& extensions);

public:

    VulkanInstance(
        std::vector<const char*> instanceExtensions
        , std::vector<const char*> layers = {}
    );

    VulkanInstance(const VulkanInstance&) = delete;

    VulkanInstance& operator=(VulkanInstance) = delete;

    VulkanInstance(VulkanInstance&&) /*noexcept*/ = delete;

    ~VulkanInstance();

    VkInstance vk() const;
};

