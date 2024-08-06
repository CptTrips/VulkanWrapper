#include "Shader.h"
#include <stdexcept>

void Shader::createDescriptorSetLayouts(const Device& device, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& descriptorSetLayoutBindings)
{

	for (const auto& bindings : descriptorSetLayoutBindings)
		descriptorSetLayouts.emplace_back(device, bindings);

}

Shader::Shader(const Device& device, const std::vector<char>& code, VkShaderStageFlagBits stage, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& descriptorSetLayoutBindings, std::vector<VkPushConstantRange> pushConstantRanges)
	: device(device.vk())
	, module()
	, stage(stage)
	, descriptorSetLayouts()
	, pushConstantRanges(pushConstantRanges)
{

	createDescriptorSetLayouts(device, descriptorSetLayoutBindings);

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

const std::vector<DescriptorSetLayout>&  Shader::getDescriptorSetLayouts() const
{

	return descriptorSetLayouts;
}

std::vector<VkDescriptorSetLayout> Shader::getDescriptorSetLayoutsVk() const
{

	std::vector<VkDescriptorSetLayout> layouts;

	for (size_t i{ 0 }; i < descriptorSetLayouts.size(); i++)
		layouts.push_back(descriptorSetLayouts[i].vk());

	return layouts;
}

std::vector<VkPushConstantRange> Shader::getPushConstantRanges() const
{

	return pushConstantRanges;
}
