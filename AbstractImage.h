#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "DeviceMemory.h"
#include "DeviceBuffer.h"
#include "Sampler.h"

class AbstractImage
{

    Device& device;

    VkImage image;
    VkImageView imageView;

    DeviceMemory memory;

    bool wasCreated;

    VkExtent3D extent;

    VkMemoryRequirements getMemoryRequirements() const;

    void bindMemory(DeviceMemory& memory);

protected:
    const Sampler* sampler;

    AbstractImage(Device& device, VkImageCreateInfo imageCreateInfo, const Sampler* sampler);

    AbstractImage(Device& device, VkImage image, VkFormat format);

    AbstractImage(const AbstractImage&) = delete;


    static VkImageCreateInfo makeImageCreateInfo(
        uint32_t width,
        uint32_t height,
        uint32_t mipLevels,
        VkFormat format,
        VkImageTiling tiling,
        VkImageUsageFlags usage
    );

    virtual VkImageViewCreateInfo makeImageViewCreateInfo(VkFormat format);

    void createImageView(VkImageViewCreateInfo imageViewCreateInfo);

public:
    friend void swap(AbstractImage& a, AbstractImage& b);

    AbstractImage(AbstractImage&& other) noexcept;

    AbstractImage& operator=(AbstractImage other) noexcept;

    ~AbstractImage();

    VkImage vk() const;

    VkImageView getImageView() const;

    void copyBuffer(const DeviceBuffer& buffer, VkImageAspectFlags aspectMask);

    void upload(void* data);

    void upload(void* data, VkDeviceSize size, VkImageAspectFlags aspectMask);

    VkDescriptorImageInfo imageInfo() const;

    VkExtent3D getExtent() const;
};

