#include "Image.h"

#include "PipelineBarrier.h"

#include <stdexcept>

void Image::createImageView(VkFormat format)
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

    if (vkCreateImageView(device.vk(), &createInfo, nullptr, &imageView) != VK_SUCCESS)
        throw std::runtime_error("failed to create texture image view!");
}

Image::Image(
	uint32_t width,
	uint32_t height,
	uint32_t mipLevels,
	VkFormat format,
	VkImageTiling tiling,
	VkImageUsageFlags usage,
    Device& device
)
	: device(device)
	, extent{ width, height, 1 }
	, image()
	, imageView()
	, sampler(device)
	, wasCreated(true)
	, memory(device.vk())
{

	VkImageCreateInfo imageInfo{};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent = extent;
	imageInfo.mipLevels = mipLevels;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = usage;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.flags = 0; // Optional
	if (vkCreateImage(device.vk(), &imageInfo, nullptr, &image) != VK_SUCCESS) {
		throw std::runtime_error("failed to create image!");
	}

	memory = DeviceMemory(device, getMemoryRequirements(), VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

	bindMemory(memory);

	createImageView(format);
}

Image::Image(Device& device, VkImage image, VkFormat format)
	: device(device)
    , image(image)
	, imageView()
	, sampler(device)
	, wasCreated(false)
	, memory(device.vk())
{

	createImageView(format);
}

Image::Image(Image&& other) noexcept
	: device(other.device)
	, image()
	, imageView()
	, sampler(other.device)
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

VkImage Image::vk() const
{
    return image;
}


VkImageView Image::getImageView() const
{
	
	return imageView;
}

VkMemoryRequirements Image::getMemoryRequirements() const
{

	VkMemoryRequirements memoryRequirements;

	vkGetImageMemoryRequirements(device.vk(), image, &memoryRequirements);

	return memoryRequirements;
}

void Image::bindMemory(DeviceMemory& memory)
{

	vkBindImageMemory(device.vk(), image, memory.vk(), 0);
}

Image::~Image()
{

    vkDestroyImageView(device.vk(), imageView, nullptr);

	if (wasCreated)
		vkDestroyImage(device.vk(), image, nullptr);
}

void Image::copyBuffer(const DeviceBuffer& buffer)
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

	barrier.layoutTransition(commandBuffer, *this);

	VkBufferImageCopy region{};

    region.bufferOffset = 0;
    region.bufferRowLength = 0;
    region.bufferImageHeight = 0;

	region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    region.imageSubresource.mipLevel = 0;
    region.imageSubresource.baseArrayLayer = 0;
    region.imageSubresource.layerCount = 1;

	region.imageOffset = { 0, 0, 0 };
	region.imageExtent = extent;

	vkCmdCopyBufferToImage(commandBuffer.vk(), buffer.vk(), image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	device.submitCommandBuffer(commandBuffer);

	device.graphicsQueueWaitIdle();
}

void Image::upload(void* data)
{

    DeviceBuffer stagingBuffer(extent.height * extent.width * extent.depth * 4, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device);

    stagingBuffer.fill(data);

    copyBuffer(stagingBuffer);
}

VkDescriptorImageInfo Image::imageInfo() const
{

    VkDescriptorImageInfo imageInfo{};

	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	imageInfo.imageView = imageView;
	imageInfo.sampler = sampler.vk();

    return imageInfo;
}

void Image::fill(void* data)
{

	memory.fill(data);
}

void swap(Image& a, Image& b)
{

	swap(a.device, b.device);
	std::swap(a.image, b.image);
	std::swap(a.imageView, b.imageView);
	swap(a.memory, b.memory);
	std::swap(a.wasCreated, b.wasCreated);
}
