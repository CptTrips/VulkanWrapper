#include "VertexShader.h"

VertexShader::VertexShader(const Device& device, const std::vector<char>& code, VkShaderStageFlagBits stage, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& descriptorSetLayoutBindings, std::vector<VkVertexInputBindingDescription> vertexBindings, std::vector<VkVertexInputAttributeDescription> attributeDescriptions, std::vector<VkPushConstantRange> pushConstantRanges)
    : Shader(device, code, stage, descriptorSetLayoutBindings, pushConstantRanges)
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
