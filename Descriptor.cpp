#include "Descriptor.h"

#include <stdexcept>

VkDescriptorBufferInfo Descriptor::extractBufferInfo(const DeviceBuffer* buffer)
{

    VkDescriptorBufferInfo bufferInfo{};

    bufferInfo.buffer = buffer->vk();
    bufferInfo.offset = 0;
    bufferInfo.range = buffer->size();

    return bufferInfo;
}

std::vector<VkDescriptorBufferInfo> Descriptor::extractBufferInfos(const std::vector<const DeviceBuffer*>& buffers)
{

    std::vector<VkDescriptorBufferInfo> bufferInfos;

    for (const DeviceBuffer* buffer : buffers)
        bufferInfos.push_back(extractBufferInfo(buffer));

    return bufferInfos;
}

/*
Descriptor::Descriptor()
    : binding()
    , bufferInfos()
{}
*/

Descriptor::Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<VkDescriptorBufferInfo> bufferInfos)
    : binding(binding)
    , bufferInfos(bufferInfos)
{

    if (binding.descriptorCount != bufferInfos.size())
        throw std::runtime_error("Descriptor count does not match buffer count");
}

Descriptor::Descriptor(const VkDescriptorSetLayoutBinding& binding, std::vector<const DeviceBuffer*> buffers)
    : Descriptor(binding, extractBufferInfos(buffers))
{

}

VkWriteDescriptorSet Descriptor::getDescriptorWrite(VkDescriptorSet descriptorSet) const
{

	VkWriteDescriptorSet descriptorWrite{};

    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrite.dstSet = descriptorSet;
    descriptorWrite.dstBinding = binding.binding;
    descriptorWrite.dstArrayElement = dstElem;
    descriptorWrite.descriptorType = binding.descriptorType;
    descriptorWrite.descriptorCount = binding.descriptorCount;
    descriptorWrite.pBufferInfo = bufferInfos.data();

	return descriptorWrite;
}
