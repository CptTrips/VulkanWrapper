#include "YUVImage.h"

YUVImage::YUVImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, Device& device)
    : Image(width, height, mipLevels, format, tiling, usage, device)
    , sampler(device)
{
}

YUVImage::YUVImage(YUVImage&& other) noexcept
    : Image(static_cast<Image&&>(other))
    , sampler(other.device)
{

}

YUVImage& YUVImage::operator=(YUVImage other) noexcept
{

    swap(*this, other);

    return *this;
}

VkDescriptorImageInfo YUVImage::imageInfo() const
{
    
    VkDescriptorImageInfo imageInfo{ Image::imageInfo() };

    imageInfo.sampler = sampler.vk();

    return imageInfo;
}

void swap(YUVImage& a, YUVImage& b)
{

    swap(static_cast<Image&>(a), static_cast<Image&>(b));

    // prolly should swap the samplers too
}
