#include "DescriptorPool.h"

#include <stdexcept>
#include <string>

std::vector<VkDescriptorSet> DescriptorPool::allocateDescriptorSets(const std::vector<VkDescriptorSetLayout>& layouts) const
{

	std::vector<VkDescriptorSet> descriptorSets(layouts.size());

	VkDescriptorSetAllocateInfo allocInfo{};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = pool;
	allocInfo.descriptorSetCount = static_cast<uint32_t>(layouts.size());
	allocInfo.pSetLayouts = layouts.data();

	//printf("Allocating %i descriptor sets\n", layouts.size());

	if (auto returnCode{ vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) }; returnCode != VK_SUCCESS)
		throw std::runtime_error("failed to allocate descriptor sets. error code " + std::to_string(returnCode));

	return descriptorSets;
}

DescriptorPool::DescriptorPool(const Device& device, const std::unordered_set<VkDescriptorType>& descriptorTypes, uint32_t descriptorSetCount)
	: device(device.vk())
	, pool()
{

	std::vector<VkDescriptorPoolSize> poolSizes;

	for (VkDescriptorType descriptorType : descriptorTypes)
		poolSizes.push_back({ descriptorType, descriptorSetCount });

	VkDescriptorPoolCreateInfo poolInfo{};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
	poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = static_cast<uint32_t>(descriptorSetCount);

	if (vkCreateDescriptorPool(device.vk(), &poolInfo, nullptr, &pool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor pool!");
	}
}
DescriptorPool::~DescriptorPool()
{

	vkDestroyDescriptorPool(device, pool, nullptr);
}

VkDescriptorPool DescriptorPool::vk() const
{

	return pool;
}

std::vector<DescriptorSet> DescriptorPool::makeDescriptorSets(const std::vector<DescriptorSetInfo>& descriptorSetInfos) const
{

	std::vector<VkDescriptorSetLayout> layouts;

	for (const DescriptorSetInfo& info : descriptorSetInfos)
		layouts.push_back(info.descriptorSetLayout->vk());

	std::vector<VkDescriptorSet> vkDescriptorSets{ allocateDescriptorSets(layouts) };

	std::vector<DescriptorSet> descriptorSets;

	for (size_t i{ 0 }; i < vkDescriptorSets.size(); i++)
		descriptorSets.emplace_back(device, vkDescriptorSets[i], descriptorSetInfos[i].descriptors);

	return descriptorSets;
}
