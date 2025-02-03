#pragma once

#include "GraphicsPipeline.h"

class GraphicsPipelineBuilder
{

    VkDevice device;

    std::vector<VkPipelineShaderStageCreateInfo> shaderStageVector;

	VkPipelineVertexInputStateCreateInfo vertexInputInfo;

    VkPrimitiveTopology topology;

public:
    GraphicsPipelineBuilder(Device& device);

    GraphicsPipeline build();

    void setVertexShader(const VertexShader& vertexShader);

    void setFragmentShader(const Shader& fragmentShader);

    void setColorFormat(VkFormat colorFormat);

    void setTopology(VkPrimitiveTopology topology);

};

