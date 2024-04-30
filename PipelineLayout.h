#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"

#include "DescriptorSetLayout.h"

class PipelineLayout
{

    VkDevice device;

    VkPipelineLayout layout;

public:
    PipelineLayout(const Device& device, const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts, const std::vector<VkPushConstantRange>& pushConstantRanges);

    ~PipelineLayout();

    VkPipelineLayout vk() const;
};
