#pragma once

#include <vulkan/vulkan.h>

#include <vector>

class CommandBuffer
{

    VkDevice device;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

    CommandBuffer() = default;

    void begin(bool singleUse) const;

public:

    std::vector<VkSemaphore> waitSemaphores;
    std::vector<VkPipelineStageFlags> waitStageFlags;
    
    std::vector<VkSemaphore> signalSemaphores;

    CommandBuffer(VkDevice device, VkCommandPool commandPool, bool singleUse = true);

    CommandBuffer(VkDevice device, VkCommandPool commandPool, VkCommandBuffer commandBuffer, bool singleUse);

    CommandBuffer(const CommandBuffer&) = delete;

    CommandBuffer(CommandBuffer&&) noexcept;

    CommandBuffer& operator=(CommandBuffer) noexcept;

    ~CommandBuffer();

    VkCommandBuffer& vk();

    void reset() const;

    void addWaitSemaphore(VkSemaphore semaphore, VkPipelineStageFlags flags);

    void addSignalSemaphore(VkSemaphore semaphore);
};

