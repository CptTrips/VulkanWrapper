#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"

class DeviceMemory
{

    VkDevice device;
    VkDeviceMemory memory;
    VkDeviceSize m_size;

public:

    friend void swap(DeviceMemory& a, DeviceMemory& b);

    DeviceMemory(VkDevice device);

    DeviceMemory(Device& device, VkMemoryRequirements memRequirements, VkMemoryPropertyFlags memProperties);

    DeviceMemory(const DeviceMemory&) = delete;

    DeviceMemory& operator=(const DeviceMemory&) = delete;

    DeviceMemory& operator=(DeviceMemory&& other) noexcept;

    ~DeviceMemory();

    void fill(void* data);

    VkDeviceSize size() const;

    VkDeviceMemory vk() const;
};
