#pragma once
#include "Image.h"
#include "YUVSampler.h"

class YUVImage :
    public Image
{

    YUVSampler sampler;

public:
    friend void swap(YUVImage& a, YUVImage& b);

    YUVImage(
        uint32_t width,
        uint32_t height,
        uint32_t mipLevels,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        Device& device
    );


    YUVImage(const YUVImage&) = delete;

    YUVImage(YUVImage&& other) noexcept;

    YUVImage& operator=(YUVImage other) noexcept;

    VkDescriptorImageInfo imageInfo() const;
};

