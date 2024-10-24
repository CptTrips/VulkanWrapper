#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include "Device.h"

#include "Shader.h"

class PipelineLayout
{

    VkDevice device;

    VkPipelineLayout layout;

    std::vector<VkDescriptorSetLayout> getDescriptorSetLayouts(const std::vector<Shader const*> shaders) const;

    std::vector<VkPushConstantRange> getPushConstantRanges(const std::vector<Shader const*> shaders) const;

public:
    PipelineLayout(const Device& device, std::vector<Shader const*> shaders);

    PipelineLayout(const Device& device, const std::vector<VkDescriptorSetLayout>& descriptorSetLayouts, const std::vector<VkPushConstantRange>& pushConstantRanges);

    ~PipelineLayout();

    VkPipelineLayout vk() const;
};
