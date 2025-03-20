#pragma once
#include "AbstractImage.h"
#include "YUVSampler.h"

class YUVImage : public AbstractImage
{

    virtual VkImageViewCreateInfo makeImageViewCreateInfo(VkFormat format) override;

    /*
    VkImageCreateInfo makeImageCreateInfo(
        uint32_t width,
        uint32_t height,
        uint32_t mipLevels,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        const YUVSampler* sampler
    ) const;
    */

public:
    //friend void swap(YUVImage& a, YUVImage& b);

    YUVImage(
        uint32_t width,
        uint32_t height,
        uint32_t mipLevels,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        const YUVSampler* sampler,
        Device& device
    );

    YUVImage(const YUVImage&) = delete;

    YUVImage(YUVImage&& other) noexcept;

    YUVImage& operator=(YUVImage other) noexcept;
};

