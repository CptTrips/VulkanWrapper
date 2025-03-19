#include "Sampler.h"

#include <stdexcept>

VkSamplerCreateInfo Sampler::makeCreateInfo(const Device& device) const
{

    VkPhysicalDeviceProperties properties{};
    vkGetPhysicalDeviceProperties(device.getPhysicalDevice(), &properties);

    VkSamplerCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    createInfo.magFilter = VK_FILTER_LINEAR;
    createInfo.minFilter = VK_FILTER_LINEAR;
    createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.anisotropyEnable = VK_TRUE;
    createInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
    createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
    createInfo.unnormalizedCoordinates = VK_FALSE;
    createInfo.compareEnable = VK_FALSE;
    createInfo.compareOp = VK_COMPARE_OP_ALWAYS;

    return createInfo;
}

Sampler::Sampler(const Device& device)
    : device(device.vk())
    , sampler()
{

    VkSamplerCreateInfo createInfo{ makeCreateInfo(device) };

    if (vkCreateSampler(device.vk(), &createInfo, nullptr, &sampler) != VK_SUCCESS)
        throw std::runtime_error("Failed to create texture sampler");
}

Sampler::Sampler(const Device& device, VkSamplerCreateInfo createInfo)
{

    if (vkCreateSampler(device.vk(), &createInfo, nullptr, &sampler) != VK_SUCCESS)
        throw std::runtime_error("Failed to create texture sampler");
}

Sampler::~Sampler()
{

    vkDestroySampler(device, sampler, nullptr);
}

VkSampler Sampler::vk() const
{

    return sampler;
}
