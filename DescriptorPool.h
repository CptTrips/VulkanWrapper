#pragma once

#include <vulkan/vulkan.h>

#include <unordered_set>
#include <vector>

#include "Device.h"
#include "DescriptorSet.h"
#include "DescriptorSetInfo.h"

class DescriptorPool
{

    VkDevice device;

    VkDescriptorPool pool;

    std::vector<VkDescriptorSet> allocateDescriptorSets(const std::vector<VkDescriptorSetLayout>& layouts) const;

public:
    DescriptorPool(const Device& device, const std::unordered_set<VkDescriptorType>& descriptorTypes, uint32_t descriptorSetCount);

    ~DescriptorPool();

    VkDescriptorPool vk() const;

    std::vector<DescriptorSet> makeDescriptorSets(const std::vector<DescriptorSetInfo>& descriptorSetInfos) const;
};

