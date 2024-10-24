#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "DescriptorSetLayout.h"


class Shader
{

    VkDevice device;

    VkShaderModule module;

    VkShaderStageFlagBits stage;

public:

    const std::vector<VkDescriptorSetLayoutBinding>& bindings;

    const std::vector<VkPushConstantRange>& pushConstantRanges;

    const DescriptorSetLayout descriptorSetLayout;

    Shader(
        const Device& device,
        const std::vector<char>& code,
        VkShaderStageFlagBits stage,
        const std::vector<VkDescriptorSetLayoutBinding>& bindings,
        const std::vector<VkPushConstantRange>& pushConstantRanges
    );

    ~Shader();

    VkPipelineShaderStageCreateInfo getPipelineShaderStageCreateInfo() const;
};
