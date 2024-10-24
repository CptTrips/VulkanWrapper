#include "PipelineLayout.h"

#include <stdexcept>

std::vector<VkDescriptorSetLayout> PipelineLayout::getDescriptorSetLayouts(const std::vector<Shader const*> shaders) const
{
	std::vector<VkDescriptorSetLayout> descriptorSetLayouts;

	for (Shader const* shader : shaders)
		descriptorSetLayouts.push_back(shader->descriptorSetLayout.vk());

	return descriptorSetLayouts;
}

std::vector<VkPushConstantRange> PipelineLayout::getPushConstantRanges(const std::vector<Shader const*> shaders) const
{
	std::vector<VkPushConstantRange> pushConstantRanges;

	for (Shader const* shader : shaders)
		for (const auto& pcr : shader->pushConstantRanges)
			pushConstantRanges.push_back(pcr);

	return pushConstantRanges;
}

PipelineLayout::PipelineLayout(const Device& device, std::vector<Shader const*> shaders)
	: PipelineLayout(device, getDescriptorSetLayouts(shaders), getPushConstantRanges(shaders))
{
}

PipelineLayout::PipelineLayout(const Device& device, const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts, const std::vector<VkPushConstantRange>& pushConstantRanges)
	: device(device.vk())
{

	VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = descriptorSetLayouts.size();
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts.data();
	pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size();
	pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data();

	if (vkCreatePipelineLayout(device.vk(), &pipelineLayoutInfo, nullptr, &layout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipeline layout!");
	}
}

PipelineLayout::~PipelineLayout()
{

	vkDestroyPipelineLayout(device, layout, nullptr);
}

VkPipelineLayout PipelineLayout::vk() const
{
	return layout;
}
