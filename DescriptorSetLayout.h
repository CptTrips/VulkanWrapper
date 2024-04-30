#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"

class DescriptorSetLayout
{

    VkDevice device;

    VkDescriptorSetLayout layout;

    DescriptorSetLayout(VkDevice device);

public:
    DescriptorSetLayout(const Device& device, const std::vector<VkDescriptorSetLayoutBinding> bindings);

    DescriptorSetLayout(const DescriptorSetLayout&) = delete;
    
    DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

    DescriptorSetLayout(DescriptorSetLayout&& other) noexcept;

    DescriptorSetLayout& operator=(DescriptorSetLayout&& other) noexcept;

    ~DescriptorSetLayout();

    friend void swap(DescriptorSetLayout& a, DescriptorSetLayout& b) noexcept;

    VkDescriptorSetLayout vk() const;
};

