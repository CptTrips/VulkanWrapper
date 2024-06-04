#include "GPUTimer.h"

void GPUTimer::writeTimestamp(CommandBuffer& commandBuffer, uint32_t timerID, VkPipelineStageFlags pipelineStages) const
{

    vkCmdResetQueryPool(commandBuffer.vk(), queryPool.vk(), timerID, 1);

    vkCmdWriteTimestamp2(commandBuffer.vk(), pipelineStages, queryPool.vk(), timerID);
}

GPUTimer::GPUTimer(const Device& device, uint32_t timerCount)
    : timerCount(timerCount)
    , queryPool(device.vk(), VK_QUERY_TYPE_TIMESTAMP, 2u * timerCount)
    , units(device.getPhysicalDeviceProperties().limits.timestampPeriod)
{

}

void GPUTimer::startTimer(CommandBuffer& commandBuffer, uint32_t timerID, VkPipelineStageFlags pipelineStages) const
{

    writeTimestamp(commandBuffer, timerID, pipelineStages);
}

void GPUTimer::stopTimer(CommandBuffer& commandBuffer, uint32_t timerID, VkPipelineStageFlags pipelineStages) const
{

    writeTimestamp(commandBuffer, timerID + timerCount, pipelineStages);
}

float GPUTimer::getTime(uint32_t timerID) const
{

    uint32_t startTimestamp{ queryPool.getResult<uint32_t>(timerID) };
    uint32_t endTimestamp{ queryPool.getResult<uint32_t>(timerID + timerCount) };

    return units * endTimestamp - units * startTimestamp;
}
