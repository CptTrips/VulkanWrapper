#include "ImageBuilder.h"

ImageBuilder::ImageBuilder(Device& device)
	: device(device)
	, yuvConversionCreateInfo{}
    , imageCreateInfo{}
{

	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
	//imageCreateInfo.extent = extent;
	//imageCreateInfo.mipLevels = mipLevels;
	imageCreateInfo.arrayLayers = 1;
	//imageCreateInfo.format = format;
	//imageCreateInfo.tiling = tiling;
	imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	//imageCreateInfo.usage = usage;
	imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageCreateInfo.flags = 0; // Optional
}


void ImageBuilder::addYUVSampler()
{

	auto result = vkCreateSamplerYcbcrConversion(device.vk(), &yuvConversionCreateInfo, nullptr, &yuvConversion);

	yuvConversionInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_YCBCR_CONVERSION_INFO;
	yuvConversionInfo.conversion = yuvConversion;

	VkSamplerCreateInfo samplerInfo{};

	samplerInfo.pNext = &yuvConversionInfo;

	
}

Image ImageBuilder::build() const
{

	return Image(device, imageCreateInfo);
}
