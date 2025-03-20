#pragma once
#include "Sampler.h"
class YUVSampler :
    public Sampler
{

    VkSamplerYcbcrConversion yuvConversion;
    VkSamplerYcbcrConversionInfo yuvConversionInfo;

    VkSamplerCreateInfo makeSamplerCreateInfo(const Device& device, VkFormat format);

public:
    YUVSampler(const Device& device, VkFormat format);

    YUVSampler(const YUVSampler&) = delete;

    YUVSampler& operator=(const YUVSampler&) = delete;

    ~YUVSampler();

    const VkSamplerYcbcrConversionInfo* getYUVConversionInfo() const;
};

