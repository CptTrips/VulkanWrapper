#pragma once

#include "Image.h"

class ImageBuilder
{

    Device& device;

    VkSamplerYcbcrConversionCreateInfo yuvConversionCreateInfo;
    VkSamplerYcbcrConversion yuvConversion;
    VkSamplerYcbcrConversionInfo yuvConversionInfo;

public:

    VkImageCreateInfo imageCreateInfo;

    ImageBuilder(Device& device);

    Image build() const;

    void addYUVSampler();
};

