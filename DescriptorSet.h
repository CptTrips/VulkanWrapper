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

public:

    DescriptorSet(VkDevice device, VkDescriptorSet descriptorSet);

    void bind(CommandBuffer& commandBuffer, VkPipelineBindPoint bindPoint, const PipelineLayout& pipelineLayout) const;

    VkDescriptorSet vk() const;
};

