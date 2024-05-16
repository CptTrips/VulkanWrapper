#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class CommandBuffer
{

    VkDevice device;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    CommandBuffer() = default;

public:

    std::vector<VkSemaphore> waitSemaphores;
    std::vector<VkPipelineStageFlags> waitStageFlags;
    
    std::vector<VkSemaphore> signalSemaphores;

    CommandBuffer(VkDevice device, VkCommandPool commandPool);

    CommandBuffer(const CommandBuffer&) = delete;

    CommandBuffer(CommandBuffer&&) noexcept;

    CommandBuffer& operator=(CommandBuffer) noexcept;

    ~CommandBuffer();

    VkCommandBuffer& vk();

    void addWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags flags);

    void addSignalSemaphore(VkSemaphore semaphore);
};

