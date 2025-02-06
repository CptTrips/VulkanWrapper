#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "DeviceMemory.h"
#include "DeviceBuffer.h"
#include "Sampler.h"

class Image
{

    Device& device;

    VkExtent3D extent;

    VkImage image;
    VkImageView imageView;

    Sampler sampler;

    DeviceMemory memory;

    bool wasCreated;

    void createImageView(VkFormat format);

    void bindMemory(DeviceMemory& memory);

    void fill(void* data);

public:

    friend void swap(Image& a, Image& b);

    Image(
        uint32_t width,
        uint32_t height,
        uint32_t mipLevels,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage,
        Device& device
    );

    Image(Device& device, VkImage image, VkFormat format);

    Image(const Image&) = delete;

    Image(Image&& other) noexcept;

    Image& operator=(Image other) noexcept;

    VkImage vk() const;

    VkImageView getImageView() const;

    VkMemoryRequirements getMemoryRequirements() const;

    ~Image();

    void copyBuffer(const DeviceBuffer& buffer);

    void upload(void* data);

    VkDescriptorImageInfo imageInfo() const;
};

