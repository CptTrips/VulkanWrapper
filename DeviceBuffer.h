#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "CommandBuffer.h"
#include "DeviceMemory.h"

class DeviceBuffer
{
    
	Device& device;
	VkBuffer buffer;
	VkDeviceSize bufferSize;
	DeviceMemory memory;

	DeviceBuffer(Device& device);

public:

	DeviceBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, Device& device);

	DeviceBuffer(const DeviceBuffer&) = delete;

	DeviceBuffer(DeviceBuffer&&) noexcept;

	DeviceBuffer& operator=(const DeviceBuffer&) = delete;

	DeviceBuffer& operator=(DeviceBuffer&&) noexcept;

	~DeviceBuffer();

	friend void swap(DeviceBuffer& a, DeviceBuffer& b) noexcept;

	void fill(const void* data);

	void copy(DeviceBuffer& src);

	void upload(const void* data);

	VkBuffer vk() const;

	VkDeviceSize size() const;

	VkDescriptorBufferInfo bufferInfo() const;
};

