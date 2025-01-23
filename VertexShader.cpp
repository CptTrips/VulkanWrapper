#include "VertexShader.h"

VertexShader::VertexShader(
    const Device& device,
    const std::vector<char>& code,
    const std::vector<VkDescriptorSetLayoutBinding>& bindings,
    const std::vector<VkPushConstantRange>& pushConstantRanges,
    const std::vector<VkVertexInputBindingDescription>& vertexBindings,
    const std::vector<VkVertexInputAttributeDescription>& attributeDescriptions
)
    : Shader(device, code, VK_SHADER_STAGE_VERTEX_BIT, bindings, pushConstantRanges)
    , vertexBindings(vertexBindings)
    , attributeDescriptions(attributeDescriptions)
{
}
