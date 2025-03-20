#include "YUVImage.h"

YUVImage::YUVImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, const YUVSampler* sampler, Device& device)
    : AbstractImage(device, makeImageCreateInfo(width, height, mipLevels, format, tiling, usage), sampler)
{

	VkImageViewCreateInfo imageViewCreateInfo{ makeImageViewCreateInfo(format) };

    createImageView(imageViewCreateInfo);
}

YUVImage::YUVImage(YUVImage&& other) noexcept
    : AbstractImage(static_cast<AbstractImage&&>(other))
{

}

YUVImage& YUVImage::operator=(YUVImage other) noexcept
{

    swap(*this, other);

    return *this;
}

VkImageViewCreateInfo YUVImage::makeImageViewCreateInfo(VkFormat format)
{

    VkImageViewCreateInfo createInfo{ AbstractImage::makeImageViewCreateInfo(format) };

    createInfo.pNext = static_cast<const YUVSampler*>(sampler)->getYUVConversionInfo();

    return createInfo;
}

/*
VkImageCreateInfo YUVImage::makeImageCreateInfo(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, const YUVSampler* sampler) const
{

    VkImageCreateInfo createInfo{ AbstractImage::makeImageCreateInfo(width, height, mipLevels, format, tiling, usage) };

    //createInfo.pNext = sampler->getYUVConversionInfo();

    return createInfo;
}
*/
