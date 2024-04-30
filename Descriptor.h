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

    int dstElem{ 0 };

public:

    //Descriptor();

    Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<VkDescriptorBufferInfo> bufferInfos);

    Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<const DeviceBuffer*> buffers);

    VkWriteDescriptorSet getDescriptorWrite(VkDescriptorSet descriptorSet) const;
};

