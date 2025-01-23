#include "FragmentShader.h"

#include "ShaderReader.h"

FragmentShader::FragmentShader(
    const Device& device,
    const std::vector<char>& code,
    const std::vector<VkDescriptorSetLayoutBinding>& bindings,
    const std::vector<VkPushConstantRange>& pushConstantRanges
)
    : Shader(device, code, VK_SHADER_STAGE_FRAGMENT_BIT, bindings, pushConstantRanges)

{
}
