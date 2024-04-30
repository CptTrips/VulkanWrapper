#include "ComputePipeline.h"

#include <stdexcept>

ComputePipeline::ComputePipeline(Device& device, Shader& computeShader)
    : device(device.vk())
    , pipeline()
    , pipelineLayout(device, computeShader.getDescriptorSetLayoutsVk(), computeShader.getPushConstantRanges())
{

    VkComputePipelineCreateInfo pipelineInfo{};

    pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;

    //pipelineInfo.flags = 0;

    pipelineInfo.stage = computeShader.getPipelineShaderStageCreateInfo();

    pipelineInfo.layout = pipelineLayout.vk();

    if (vkCreateComputePipelines(device.vk(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS)
        throw std::runtime_error("Compute pipeline creation failed");
}

ComputePipeline::~ComputePipeline()
{

    vkDestroyPipeline(device, pipeline, nullptr);
}

void ComputePipeline::bind(CommandBuffer& commandBuffer) const
{

	vkCmdBindPipeline(commandBuffer.vk(), VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);
}

const PipelineLayout& ComputePipeline::getLayout() const
{

    return pipelineLayout;
}
