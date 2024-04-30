#include "DescriptorSet.h"

void DescriptorSet::writeDescriptors(const std::vector<Descriptor>& descriptors)
{

	std::vector<VkWriteDescriptorSet> descriptorWrites(descriptors.size());

	for (int i = 0; i < descriptors.size(); i++)
	{

		descriptorWrites[i] = descriptors[i].getDescriptorWrite(descriptorSet);
	}

	vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
}

DescriptorSet::DescriptorSet(VkDevice device, VkDescriptorSet descriptorSet, const std::vector<Descriptor>& descriptors)
	: device(device)
	, descriptorSet(descriptorSet)
{

	writeDescriptors(descriptors);
}

void DescriptorSet::bind(CommandBuffer& commandBuffer, VkPipelineBindPoint bindPoint, const PipelineLayout& pipelineLayout) const
{

	vkCmdBindDescriptorSets(commandBuffer.vk(), VK_PIPELINE_BIND_POINT_COMPUTE, pipelineLayout.vk(), 0, 1, &descriptorSet, 0, nullptr);
}
