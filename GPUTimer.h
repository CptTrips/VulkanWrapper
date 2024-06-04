#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "QueryPool.h"
#include "CommandBuffer.h"

class GPUTimer
{

    const uint32_t timerCount;

    QueryPool queryPool;

    float units;

    std::vector<uint32_t> startQueries, endQueries;

    void writeTimestamp(CommandBuffer& commandBuffer, uint32_t timerID, VkPipelineStageFlags pipelineStages) const;

public:
    GPUTimer(const Device& device, uint32_t timerCount);

    void startTimer(CommandBuffer& commandBuffer, uint32_t timerID, VkPipelineStageFlags pipelineStages) const;

    void stopTimer(CommandBuffer& commandBuffer, uint32_t timerID, VkPipelineStageFlags pipelineStages) const;

    // nanoseconds
    float getTime(uint32_t timerID) const;
};

