#pragma once

#include <vulkan/vulkan.h>   

#include "QueueFamilyIndices.h"
#include "SwapChainSupportDetails.h"
#include "CommandPool.h"
#include "CommandBuffer.h"
#include "Fence.h"

#include <vector>

// Finds a physical device appropriate for the surface
class Device
{

    QueueFamilyIndices queueFamilyIndices;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
	VkDevice device;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

    VkCommandPool commandPool;

    VkDescriptorPool descriptorPool;

    bool checkPhysicalDevice(VkPhysicalDevice device);

    bool checkPhysicalDeviceFeatures(VkPhysicalDevice device) const;

    bool checkPhysicalDeviceProperties(VkPhysicalDevice device) const;

    VkPhysicalDevice pickPhysicalDevice(VkInstance instance);

    VkDevice createDevice(const std::vector<const char*>& deviceExtensions, const std::vector<const char*>& layers);
    
    void getQueues();

    void createCommandPool();

    void destroyCommandPool();

    static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);

public:

    Device(VkInstance instance, VkSurfaceKHR surface, const std::vector<const char*>& deviceExtensions, const std::vector<const char*>& layers);

    Device(const Device&) = delete;

    Device& operator=(Device) = delete;

    ~Device();

    friend void swap(Device& a, Device& b);

    QueueFamilyIndices findQueueFamilies() const;

    VkPhysicalDeviceProperties getPhysicalDeviceProperties() const;

    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) const;

    bool checkLinearBlittSupport(VkFormat imageFormat) const;

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) const;

    VkDevice vk() const;

	SwapChainSupportDetails querySwapChainSupport() const;

    VkQueue getPresentQueue() const;

    VkQueue getGraphicsQueue() const;

    CommandBuffer makeSingleUseCommandBuffer();

    std::vector<CommandBuffer> makeCommandBuffers(uint32_t size, bool singleUse) const;

    void submitCommandBuffer(CommandBuffer& commandBuffer, VkFence fence = VK_NULL_HANDLE);

    void graphicsQueueWaitIdle() const;

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    VkPhysicalDevice getPhysicalDevice() const;

};

