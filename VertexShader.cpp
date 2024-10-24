#include "VertexShader.h"

VertexShader::VertexShader(
    const Device& device,
    const std::vector<char>& code,
    VkShaderStageFlagBits stage,
    const std::vector<VkDescriptorSetLayoutBinding>& bindings,
    const std::vector<VkPushConstantRange>& pushConstantRanges,
    const std::vector<VkVertexInputBindingDescription>& vertexBindings,
    const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions
)
    : Shader(device, code, stage, bindings, pushConstantRanges)
    , vertexBindings(vertexBindings)
    , attributeDescriptions(attributeDescriptions)
{
}
