#include "AbstractImage.h"
#include "PipelineBarrier.h"

#include <stdexcept>

AbstractImage::AbstractImage(Device& device, VkImageCreateInfo imageCreateInfo, const Sampler* sampler)
    : device(device)
    , image()
    , imageView()
    , memory(device.vk())
	, wasCreated(true)
	, extent(imageCreateInfo.extent)
	, sampler(sampler)
{

	if (vkCreateImage(device.vk(), &imageCreateInfo, nullptr, &image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	memory = DeviceMemory(device, getMemoryRequirements(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	bindMemory(memory);

}

AbstractImage::AbstractImage(Device& device, VkImage image, VkFormat format)
	: device(device)
    , image(image)
	, imageView()
	, memory(device.vk())
	, wasCreated(false)
	, extent()
	, sampler(nullptr)
{

	VkImageViewCreateInfo imageViewCreateInfo{ makeImageViewCreateInfo(format) };

	createImageView(imageViewCreateInfo);
}

AbstractImage::AbstractImage(AbstractImage&& other) noexcept
	: device(other.device)
	, wasCreated(false)
	, memory(other.device.vk())
	, extent()
	, image()
	, imageView()
	, sampler()
{

	swap(*this, other);
}

AbstractImage& AbstractImage::operator=(AbstractImage other) noexcept
{

	swap(*this, other);

	return *this;
}

AbstractImage::~AbstractImage()
{

    vkDestroyImageView(device.vk(), imageView, nullptr);

	if (wasCreated)
		vkDestroyImage(device.vk(), image, nullptr);
}

VkImage AbstractImage::vk() const
{
	return image;
}

VkMemoryRequirements AbstractImage::getMemoryRequirements() const
{

	VkMemoryRequirements memoryRequirements;

	vkGetImageMemoryRequirements(device.vk(), image, &memoryRequirements);

	return memoryRequirements;
}

VkImageCreateInfo AbstractImage::makeImageCreateInfo(uint32_t width, uint32_t height, uint32_t mipLevels, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage)
{

	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent = { width, height, 1 };
	imageInfo.mipLevels = mipLevels;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.flags = 0; // Optional

	return imageInfo;
}

VkImageViewCreateInfo AbstractImage::makeImageViewCreateInfo(VkFormat format)
{

	VkImageViewCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	createInfo.image = image;
	createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	createInfo.format = format;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

	return createInfo;
}

void AbstractImage::createImageView(VkImageViewCreateInfo imageViewCreateInfo)
{

    if (vkCreateImageView(device.vk(), &imageViewCreateInfo, nullptr, &imageView) != VK_SUCCESS)
        throw std::runtime_error("failed to create texture image view!");
}

void AbstractImage::bindMemory(DeviceMemory& memory)
{

	vkBindImageMemory(device.vk(), image, memory.vk(), 0);
}

VkImageView AbstractImage::getImageView() const
{
	
	return imageView;
}

void AbstractImage::copyBuffer(const DeviceBuffer& buffer, VkImageAspectFlags aspectMask)
{

	CommandBuffer commandBuffer{ device.makeSingleUseCommandBuffer() };

    PipelineStage pipelineStageInitial{};
	pipelineStageInitial.layout = VK_IMAGE_LAYOUT_UNDEFINED;
	pipelineStageInitial.accessFlags = 0;
	pipelineStageInitial.stageFlags = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;

    PipelineStage pipelineStageTransferDst{};
	pipelineStageTransferDst.layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	pipelineStageTransferDst.accessFlags = VK_ACCESS_TRANSFER_WRITE_BIT;
	pipelineStageTransferDst.stageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;

	PipelineBarrier barrier(pipelineStageInitial, pipelineStageTransferDst);

	barrier.layoutTransition(commandBuffer, image);

	VkBufferImageCopy region{};

    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = aspectMask;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = extent;

	vkCmdCopyBufferToImage(commandBuffer.vk(), buffer.vk(), image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	device.submitCommandBuffer(commandBuffer);

	device.graphicsQueueWaitIdle();
}

void AbstractImage::upload(void* data)
{

	upload(data, extent.height * extent.width * extent.depth * 4, VK_IMAGE_ASPECT_COLOR_BIT);
}

void AbstractImage::upload(void* data, VkDeviceSize size, VkImageAspectFlags aspectMask)
{

    DeviceBuffer stagingBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device);

    stagingBuffer.fill(data);

    copyBuffer(stagingBuffer, aspectMask);
}

VkDescriptorImageInfo AbstractImage::imageInfo() const
{

    VkDescriptorImageInfo imageInfo{};

	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = imageView;
	imageInfo.sampler = (sampler) ? sampler->vk() : VK_NULL_HANDLE;

    return imageInfo;
}

VkExtent3D AbstractImage::getExtent() const
{
	return extent;
}

void swap(AbstractImage& a, AbstractImage& b)
{

	swap(a.device, b.device);
	std::swap(a.image, b.image);
	std::swap(a.imageView, b.imageView);
	swap(a.memory, b.memory);
	std::swap(a.wasCreated, b.wasCreated);
	std::swap(a.sampler, b.sampler);
	std::swap(a.extent, b.extent);
}
