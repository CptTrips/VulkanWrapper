#include "CommandBuffer.h"

#include <utility>
#include <stdexcept>

CommandBuffer::CommandBuffer(VkDevice device, VkCommandPool commandPool, bool singleUse)
    : device(device)
    , commandPool(commandPool)
    , commandBuffer()
{

	VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = commandPool;
    allocInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

    begin(singleUse);
}

CommandBuffer::CommandBuffer(
    VkDevice device,
    VkCommandPool commandPool,
    VkCommandBuffer commandBuffer,
    bool singleUse
)
    : device(device)
    , commandPool(commandPool)
    , commandBuffer(commandBuffer)
{

    begin(singleUse);
}

CommandBuffer::CommandBuffer(CommandBuffer&& other) noexcept
    : device(other.device)
    , commandPool(other.commandPool)
    , commandBuffer(VK_NULL_HANDLE)
{

    std::swap(commandBuffer, other.commandBuffer);

    std::swap(waitSemaphores, other.waitSemaphores);
    std::swap(waitStageFlags, other.waitStageFlags);
    std::swap(signalSemaphores, other.signalSemaphores);
}

CommandBuffer& CommandBuffer::operator=(CommandBuffer other) noexcept
{

    std::swap(device, other.device);
    std::swap(commandPool, other.commandPool);
    std::swap(commandBuffer, other.commandBuffer);
    std::swap(waitSemaphores, other.waitSemaphores);
    std::swap(waitStageFlags, other.waitStageFlags);
    std::swap(signalSemaphores, other.signalSemaphores);

    return *this;
}

CommandBuffer::~CommandBuffer()
{

	vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
}

VkCommandBuffer& CommandBuffer::vk()
{

    return commandBuffer;
}

void CommandBuffer::addWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags flags)
{

    waitSemaphores.push_back(semaphore);

    waitStageFlags.push_back(flags);
}

void CommandBuffer::addSignalSemaphore(VkSemaphore semaphore)
{

    signalSemaphores.push_back(semaphore);
}

void CommandBuffer::reset() const
{

    vkResetCommandBuffer(commandBuffer, 0);

    begin(false);
}

void CommandBuffer::begin(bool singleUse) const
{

	VkCommandBufferBeginInfo beginInfo{};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    VkCommandBufferUsageFlags flags{};

    if (singleUse)
        flags = flags | VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        
	beginInfo.flags = flags;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("failed to begin recording command buffer!");
}
