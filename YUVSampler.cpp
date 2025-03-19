#include "YUVSampler.h"

#include <stdexcept>

VkSamplerCreateInfo YUVSampler::makeSamplerCreateInfo(const Device& device)
{
    
    VkSamplerYcbcrConversionCreateInfo yuvConversionCreateInfo{};

    yuvConversionCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_CREATE_INFO;
    yuvConversionCreateInfo.format = VK_FORMAT_G8_B8_R8_3PLANE_444_UNORM;
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

    return samplerCreateInfo;
}

YUVSampler::YUVSampler(const Device& device)
    : Sampler(device, makeSamplerCreateInfo(device))
{

}

YUVSampler::~YUVSampler()
{

    vkDestroySamplerYcbcrConversion(device, yuvConversion, nullptr);
}
