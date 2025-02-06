#pragma once

#include <vulkan/vulkan.h>

#include <vector>

#include "DeviceBuffer.h"

class Descriptor
{

private:

    static VkDescriptorBufferInfo extractBufferInfo(const DeviceBuffer* buffer);

    static std::vector<VkDescriptorBufferInfo> extractBufferInfos(const std::vector<const DeviceBuffer*>& buffers);

    const VkDescriptorSetLayoutBinding& binding;

    std::vector<VkDescriptorBufferInfo> bufferInfos;

    std::vector<VkDescriptorImageInfo> imageInfos;

    int dstElem{ 0 };

public:

    //Descriptor();

    Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<VkDescriptorBufferInfo> bufferInfos);

    Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<const DeviceBuffer*> buffers);

    Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<VkDescriptorImageInfo> imageInfos);

    VkWriteDescriptorSet getDescriptorWrite(VkDescriptorSet descriptorSet) const;
};

