#pragma once

#include <unordered_map>

#include <vulkan/vulkan.h>

#include "Device.h"

class DescriptorSetLayout
{

    VkDevice device;

    VkDescriptorSetLayout layout;

    DescriptorSetLayout(VkDevice device);

    std::unordered_map<VkDescriptorType, uint32_t> typeCounts;

    std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindingMap;

public:
    DescriptorSetLayout(const Device& device, const std::vector<VkDescriptorSetLayoutBinding> bindings);

    DescriptorSetLayout(const DescriptorSetLayout&) = delete;
    
    DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

    DescriptorSetLayout(DescriptorSetLayout&& other) noexcept;

    DescriptorSetLayout& operator=(DescriptorSetLayout&& other) noexcept;

    ~DescriptorSetLayout();

    friend void swap(DescriptorSetLayout& a, DescriptorSetLayout& b) noexcept;

    VkDescriptorSetLayout vk() const;

    std::unordered_map<VkDescriptorType, uint32_t> getTypeCounts() const;

    VkDescriptorSetLayoutBinding getBinding(uint32_t binding);
};

