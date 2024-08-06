#pragma once

#include "Shader.h"

class VertexShader : public Shader
{

    std::vector<VkVertexInputBindingDescription> vertexBindings;

    std::vector<VkVertexInputAttributeDescription> attributeDescriptions;

public:

    VertexShader(const Device& device, const std::vector<char>& code, VkShaderStageFlagBits stage, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& descriptorSetLayoutBindings, std::vector<VkVertexInputBindingDescription> vertexBindings, std::vector<VkVertexInputAttributeDescription> attributeDescriptions, std::vector<VkPushConstantRange> pushConstantRanges);

    std::vector<VkVertexInputBindingDescription>& getVertexBindings();

    std::vector<VkVertexInputAttributeDescription>& getAttributeDescriptions();
};

