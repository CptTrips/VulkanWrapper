#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "DeviceBuffer.h"
#include "PipelineLayout.h"
#include "Descriptor.h"

#include <stdexcept>

class DescriptorSet
{

    VkDevice device;

    VkDescriptorSet descriptorSet;

    void writeDescriptors(const std::vector<Descriptor>& descriptors);

public:

    DescriptorSet(VkDevice device, VkDescriptorSet descriptorSet, const std::vector<Descriptor>& descriptors);

    void bind(CommandBuffer& commandBuffer, VkPipelineBindPoint bindPoint, const PipelineLayout& pipelineLayout) const;
};

