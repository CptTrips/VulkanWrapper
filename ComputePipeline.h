#pragma once

#include <vulkan/vulkan.h>

#include <string>

#include "Device.h"
#include "PipelineLayout.h"
#include "CommandBuffer.h"
#include "Shader.h"

class ComputePipeline
{

    VkDevice device;

    VkPipeline pipeline;

    PipelineLayout pipelineLayout;

public:
    ComputePipeline(Device& device, Shader& computeShader);

    ~ComputePipeline();

    void bind(CommandBuffer& commandBuffer) const;

    const PipelineLayout& getLayout() const;
};

