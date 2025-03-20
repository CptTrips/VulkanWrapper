#include "YUVImage.h"

YUVImage::YUVImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, const YUVSampler* sampler, Device& device)
    : Image(device, nullptr, makeCreateInfo(width, height, mipLevels, format, tiling, usage, sampler))
    , sampler(sampler)
{
}

YUVImage::YUVImage(YUVImage&& other) noexcept
    : Image(static_cast<Image&&>(other))
    , sampler()
{

}

YUVImage& YUVImage::operator=(YUVImage other) noexcept
{

    swap(*this, other);

    return *this;
}

VkImageCreateInfo YUVImage::makeCreateInfo(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, const YUVSampler* sampler) const
{

    VkImageCreateInfo createInfo{ Image::makeCreateInfo(width, height, mipLevels, format, tiling, usage) };

    createInfo.pNext = sampler->getYUVConversionInfo();

    return createInfo;
}

VkDescriptorImageInfo YUVImage::imageInfo() const
{
    
    VkDescriptorImageInfo imageInfo{ Image::imageInfo() };

    imageInfo.sampler = sampler->vk();

    return imageInfo;
}

void swap(YUVImage& a, YUVImage& b)
{

    swap(static_cast<Image&>(a), static_cast<Image&>(b));

    // prolly should swap the samplers too
}
