#include "Image.h"

#include "PipelineBarrier.h"

#include <stdexcept>

Image::Image(Device& device, const Sampler* sampler, VkImageCreateInfo createInfo)
	:AbstractImage(device, createInfo, sampler)
{

	createImageView(makeImageViewCreateInfo(createInfo.format));
}

Image::Image(
	uint32_t width,
	uint32_t height,
	uint32_t mipLevels,
	VkFormat format,
	VkImageTiling tiling,
	VkImageUsageFlags usage,
	const Sampler* sampler,
    Device& device
)
	:AbstractImage(device, makeImageCreateInfo(width, height, mipLevels, format, tiling, usage), sampler)
{

	createImageView(makeImageViewCreateInfo(format));
}

Image::Image(Device& device, VkImage image, VkFormat format)
	: AbstractImage(device, image, format)
{

	createImageView(makeImageViewCreateInfo(format));
}

/*
Image::Image(Image&& other) noexcept
	: device(other.device)
	, image()
	, imageView()
	, sampler()
	, wasCreated(false)
	, memory(other.device.vk())
{

	swap(*this, other);
}

Image& Image::operator=(Image other) noexcept
{

	swap(*this, other);

	return *this;
}

void swap(Image& a, Image& b)
{

}
*/
