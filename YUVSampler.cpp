#include "YUVSampler.h"

#include <stdexcept>

VkSamplerCreateInfo YUVSampler::makeSamplerCreateInfo(const Device& device, VkFormat format)
{
    
    VkSamplerYcbcrConversionCreateInfo yuvConversionCreateInfo{};

    yuvConversionCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
    yuvConversionCreateInfo.format = format;
    yuvConversionCreateInfo.ycbcrModel = VK_SAMPLER_YCBCR_MODEL_CONVERSION_YCBCR_709;
    yuvConversionCreateInfo.ycbcrRange = VK_SAMPLER_YCBCR_RANGE_ITU_FULL;
    yuvConversionCreateInfo.components = {
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY
    };
    yuvConversionCreateInfo.chromaFilter = VK_FILTER_LINEAR;

	if (auto result = vkCreateSamplerYcbcrConversion(device.vk(), &yuvConversionCreateInfo, nullptr, &yuvConversion); result != VK_SUCCESS)
        throw std::runtime_error("failed to create Sampler YCbCr conversion!");

	yuvConversionInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
	yuvConversionInfo.conversion = yuvConversion;

    VkSamplerCreateInfo samplerCreateInfo{makeCreateInfo(device)};

    samplerCreateInfo.pNext = &yuvConversionInfo;
    samplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    samplerCreateInfo.anisotropyEnable = VK_FALSE;
    samplerCreateInfo.unnormalizedCoordinates = VK_FALSE;

    return samplerCreateInfo;
}

YUVSampler::YUVSampler(const Device& device, VkFormat format)
    : Sampler(device, makeSamplerCreateInfo(device, format))
{

}

YUVSampler::~YUVSampler()
{

    vkDestroySamplerYcbcrConversion(device, yuvConversion, nullptr);
}

const VkSamplerYcbcrConversionInfo* YUVSampler::getYUVConversionInfo() const
{
    return &yuvConversionInfo;
}
