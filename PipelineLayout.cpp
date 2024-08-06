#include "PipelineLayout.h"

#include <stdexcept>

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
