#pragma once

#include "vulkan/vulkan.h"

#include "Device.h"

class Sampler
{

    VkDevice device;
    VkSampler sampler;

public:
    Sampler(const Device& device);

    Sampler(const Device& device, VkSamplerCreateInfo createInfo);

    Sampler(const Sampler&) = delete;

    Sampler& operator=(const Sampler&) = delete;

    ~Sampler();

    VkSampler vk() const;
};

