#include "VertexShader.h"

VertexShader::VertexShader(const Device& device, const std::vector<char>& code, VkShaderStageFlagBits stage, const std::vector<DescriptorSetLayout>& descriptorSetLayouts, std::vector<VkVertexInputBindingDescription> vertexBindings, std::vector<VkVertexInputAttributeDescription> attributeDescriptions, std::vector<VkPushConstantRange> pushConstantRanges)
    : Shader(device, code, stage, descriptorSetLayouts, pushConstantRanges)
    , vertexBindings(vertexBindings)
    , attributeDescriptions(attributeDescriptions)
{
}

std::vector<VkVertexInputBindingDescription>& VertexShader::getVertexBindings()
{

    return vertexBindings;
}

std::vector<VkVertexInputAttributeDescription>& VertexShader::getAttributeDescriptions()
{

    return attributeDescriptions;
}
