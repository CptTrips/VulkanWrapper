#include "DescriptorSet.h"

DescriptorSet::DescriptorSet(VkDevice device, VkDescriptorSet descriptorSet)
	: device(device)
	, descriptorSet(descriptorSet)
{
}

void DescriptorSet::bind(CommandBuffer& commandBuffer, VkPipelineBindPoint bindPoint, const PipelineLayout& pipelineLayout) const
{

	vkCmdBindDescriptorSets(commandBuffer.vk(), VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout.vk(), 0, 1, &descriptorSet, 0, nullptr);
}

VkDescriptorSet DescriptorSet::vk() const
{
	return descriptorSet;
}
