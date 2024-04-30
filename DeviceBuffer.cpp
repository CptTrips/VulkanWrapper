#include "DeviceBuffer.h"

#include <stdexcept>

DeviceBuffer::DeviceBuffer(Device& device)
    : device(device)
    , buffer()
    , memory()
    , _size(0)
{
}

DeviceBuffer::DeviceBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, Device& device)
    : device(device)
    , buffer()
    , memory()
    , _size(size)
{

	VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(device.vk(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to create buffer!");
    }

    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device.vk(), buffer, &memRequirements);

    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, properties);

    if (vkAllocateMemory(device.vk(), &allocInfo, nullptr, &memory) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    vkBindBufferMemory(device.vk(), buffer, memory, 0);
}

DeviceBuffer::DeviceBuffer(DeviceBuffer&& other) noexcept
    : DeviceBuffer(other.device)
{

    swap(*this, other);
}

DeviceBuffer& DeviceBuffer::operator=(DeviceBuffer&& other) noexcept
{

    swap(*this, other);

    return *this;
}

DeviceBuffer::~DeviceBuffer()
{

	vkDestroyBuffer(device.vk(), buffer, nullptr);
    vkFreeMemory(device.vk(), memory, nullptr);
}

void DeviceBuffer::fill(void* data)
{

	void* deviceData;

	vkMapMemory(device.vk(), memory, 0, _size, 0, &deviceData);
	memcpy(deviceData, data, static_cast<size_t>(_size));
	vkUnmapMemory(device.vk(), memory);
}

void DeviceBuffer::copy(DeviceBuffer& src)
{

    CommandBuffer commandBuffer = device.makeSingleUseCommandBuffer();

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = _size;
	vkCmdCopyBuffer(commandBuffer.vk(), src.buffer, buffer, 1, &copyRegion);

    device.submitCommandBuffer(commandBuffer);

    device.graphicsQueueWaitIdle();
}

void DeviceBuffer::upload(void* data, size_t size)
{

    DeviceBuffer stagingBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device);

    stagingBuffer.fill(data);

    copy(stagingBuffer);
}

VkBuffer DeviceBuffer::vk() const
{

    return buffer;
}

VkDeviceSize DeviceBuffer::size() const
{

    return _size;
}

void swap(DeviceBuffer& a, DeviceBuffer& b) noexcept
{

    swap(a.device, b.device);
    std::swap(a.buffer, b.buffer);
    std::swap(a.memory, b.memory);
    std::swap(a._size, b._size);
}
