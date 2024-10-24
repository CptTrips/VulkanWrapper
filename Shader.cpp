#include "Shader.h"
#include <stdexcept>

Shader::Shader(
	const Device& device,
    const std::vector<char>& code,
    VkShaderStageFlagBits stage,
    const std::vector<VkDescriptorSetLayoutBinding>& bindings,
    const std::vector<VkPushConstantRange>& pushConstantRanges
)
	: device(device.vk())
	, module()
	, stage(stage)
	, bindings(bindings)
	, pushConstantRanges(pushConstantRanges)
	, descriptorSetLayout(device, bindings)
{

	VkShaderModuleCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

	if (vkCreateShaderModule(device.vk(), &createInfo, nullptr, &module) != VK_SUCCESS) {
		throw std::runtime_error("failed to create shader module!");
	}
}

Shader::~Shader()
{

	vkDestroyShaderModule(device, module, nullptr);
}

VkPipelineShaderStageCreateInfo Shader::getPipelineShaderStageCreateInfo() const
{

	VkPipelineShaderStageCreateInfo shaderStageInfo{};
	shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	shaderStageInfo.stage = stage;
	shaderStageInfo.module = module;
	shaderStageInfo.pName = "main";

	return shaderStageInfo;
}

