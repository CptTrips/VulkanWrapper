#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "CommandBuffer.h"

class DeviceBuffer
{
    
	Device& device;
	VkBuffer buffer;
	VkDeviceMemory memory;
	VkDeviceSize _size;

	DeviceBuffer(Device& device);

public:

	DeviceBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, Device& device);

	DeviceBuffer(const DeviceBuffer&) = delete;

	DeviceBuffer(DeviceBuffer&&) noexcept;

	DeviceBuffer& operator=(const DeviceBuffer&) = delete;

	DeviceBuffer& operator=(DeviceBuffer&&) noexcept;

	~DeviceBuffer();

	friend void swap(DeviceBuffer& a, DeviceBuffer& b) noexcept;

	void fill(void* data);

	void copy(DeviceBuffer& src);

	void upload(void* data, size_t size);

	VkBuffer vk() const;

	VkDeviceSize size() const;
};

