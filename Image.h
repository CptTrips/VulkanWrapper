#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "DeviceMemory.h"
#include "DeviceBuffer.h"
#include "AbstractImage.h"
#include "Sampler.h"

class Image : public AbstractImage
{

public:

    //friend void swap(Image& a, Image& b);

    Image(Device& device, const Sampler* sampler, VkImageCreateInfo createInfo);

    Image(
        uint32_t width,
        uint32_t height,
        uint32_t mipLevels,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        const Sampler* sampler,
        Device& device
    );

    Image(Device& device, VkImage image, VkFormat format);

    //Image(const Image&) = delete;

    //Image(Image&& other) noexcept;

    //Image& operator=(Image other) noexcept;

    //~Image();

};

