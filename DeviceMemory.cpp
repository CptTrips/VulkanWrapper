#include "DeviceMemory.h"

#include <stdexcept>
#include <utility>

DeviceMemory::DeviceMemory(VkDevice device)
	: device(device)
	, memory(VK_NULL_HANDLE)
	, m_size(0)
{
}

DeviceMemory::DeviceMemory(Device& device, VkMemoryRequirements memRequirements, VkMemoryPropertyFlags memProperties)
	: device(device.vk())
	, memory(VK_NULL_HANDLE)
	, m_size(memRequirements.size)
{

	VkMemoryAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, memProperties);

	if (vkAllocateMemory(device.vk(), &allocInfo, nullptr, &memory) != VK_SUCCESS) {
		throw std::runtime_error("failed to allocate image memory!");
	}
}

DeviceMemory& DeviceMemory::operator=(DeviceMemory&& other) noexcept
{

	swap(*this, other);

	return *this;
}

DeviceMemory::~DeviceMemory()
{

	if (device)
        vkFreeMemory(device, memory, nullptr);

	if (!device && memory)
		std::runtime_error("DeviceMemory has memory but no device");
}

void DeviceMemory::fill(void* data)
{

	void* deviceData;

	vkMapMemory(device, memory, 0, m_size, 0, &deviceData);
	memcpy(deviceData, data, static_cast<size_t>(m_size));
	vkUnmapMemory(device, memory);
}

VkDeviceSize DeviceMemory::size() const
{

	return m_size;
}

VkDeviceMemory DeviceMemory::vk() const
{

	return memory;
}

void swap(DeviceMemory& a, DeviceMemory& b)
{

	std::swap(a.memory, b.memory);

	std::swap(a.device, b.device);

	std::swap(a.m_size, b.m_size);
}
