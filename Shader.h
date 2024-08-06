#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "DescriptorSetLayout.h"
#include "DescriptorSet.h"


class Shader
{

    VkDevice device;

    VkShaderModule module;

    VkShaderStageFlagBits stage;

    std::vector<DescriptorSetLayout> descriptorSetLayouts;

    std::vector<VkPushConstantRange> pushConstantRanges;

protected:
    void createDescriptorSetLayouts(const Device& device, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& descriptorSetLayoutBindings);

public:

    Shader(const Device& device, const std::vector<char>& code, VkShaderStageFlagBits stage, const std::vector<std::vector<VkDescriptorSetLayoutBinding>>& descriptorSetLayoutBindings, std::vector<VkPushConstantRange> pushConstantRanges);

    ~Shader();

    VkPipelineShaderStageCreateInfo getPipelineShaderStageCreateInfo() const;

    const std::vector<DescriptorSetLayout>& getDescriptorSetLayouts() const;

    std::vector<VkDescriptorSetLayout> getDescriptorSetLayoutsVk() const;

    std::vector<VkPushConstantRange> getPushConstantRanges() const;

};
