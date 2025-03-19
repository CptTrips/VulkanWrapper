#pragma once

#include "vulkan/vulkan.h"

#include "Device.h"

class Sampler
{

protected:
    VkDevice device;
    VkSampler sampler;

    VkSamplerCreateInfo makeCreateInfo(const Device& device) const;

public:
    Sampler(const Device& device);

    Sampler(const Device& device, VkSamplerCreateInfo createInfo);

    Sampler(const Sampler&) = delete;

    Sampler& operator=(const Sampler&) = delete;

    ~Sampler();

    VkSampler vk() const;
};

