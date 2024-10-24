#pragma once

#include "Shader.h"

class VertexShader : public Shader
{

public:

    const std::vector<VkVertexInputBindingDescription>& vertexBindings;

    const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions;

    VertexShader(
        const Device& device,
        const std::vector<char>& code,
        VkShaderStageFlagBits stage,
        const std::vector<VkDescriptorSetLayoutBinding>& bindings,
        const std::vector<VkPushConstantRange>& pushConstantRanges,
        const std::vector<VkVertexInputBindingDescription>& vertexBindings,
        const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions
    );
};

