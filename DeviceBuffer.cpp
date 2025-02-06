#include "DeviceBuffer.h"

#include <stdexcept>

DeviceBuffer::DeviceBuffer(Device& device)
    : device(device)
    , buffer()
    , memory(device.vk())
{
}

DeviceBuffer::DeviceBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, Device& device)
    : device(device)
    , buffer()
    , memory(device.vk())
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

    memory = DeviceMemory(device, memRequirements, properties);

    vkBindBufferMemory(device.vk(), buffer, memory.vk(), 0);
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
}

void DeviceBuffer::fill(void* data)
{

    memory.fill(data);
}

void DeviceBuffer::copy(DeviceBuffer& src)
{

    CommandBuffer commandBuffer = device.makeSingleUseCommandBuffer();

	VkBufferCopy copyRegion{};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = memory.size();
	vkCmdCopyBuffer(commandBuffer.vk(), src.buffer, buffer, 1, &copyRegion);

    device.submitCommandBuffer(commandBuffer);

    device.graphicsQueueWaitIdle();
}

void DeviceBuffer::upload(void* data)
{

    DeviceBuffer stagingBuffer(memory.size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device);

    stagingBuffer.fill(data);

    copy(stagingBuffer);
}

VkBuffer DeviceBuffer::vk() const
{

    return buffer;
}

VkDeviceSize DeviceBuffer::size() const
{

    return memory.size();
}

VkDescriptorBufferInfo DeviceBuffer::bufferInfo() const
{

    VkDescriptorBufferInfo bufferInfo{};

    bufferInfo.buffer = buffer;
    bufferInfo.offset = 0;
    bufferInfo.range = size();

    return bufferInfo;
}

void swap(DeviceBuffer& a, DeviceBuffer& b) noexcept
{

    swap(a.device, b.device);
    std::swap(a.buffer, b.buffer);
    swap(a.memory, b.memory);
}
