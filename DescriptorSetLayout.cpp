#include "DescriptorSetLayout.h"

#include <stdexcept>
#include <utility>

DescriptorSetLayout::DescriptorSetLayout(VkDevice device)
	: device(device)
	, layout(VK_NULL_HANDLE)
{
}

DescriptorSetLayout::DescriptorSetLayout(const Device& device, const std::vector<VkDescriptorSetLayoutBinding> bindings)
	: device(device.vk())
{

	VkDescriptorSetLayoutCreateInfo layoutInfo{};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
	layoutInfo.pBindings = bindings.data();

	if (vkCreateDescriptorSetLayout(device.vk(), &layoutInfo, nullptr, &layout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

DescriptorSetLayout::DescriptorSetLayout(DescriptorSetLayout&& other) noexcept
	: DescriptorSetLayout(other.device)
{

	swap(*this, other);
}

DescriptorSetLayout& DescriptorSetLayout::operator=(DescriptorSetLayout&& other) noexcept
{

	swap(*this, other);

	return *this;
}

DescriptorSetLayout::~DescriptorSetLayout()
{

	vkDestroyDescriptorSetLayout(device, layout, nullptr);
}

VkDescriptorSetLayout DescriptorSetLayout::vk() const
{
    return layout;
}

void swap(DescriptorSetLayout& a, DescriptorSetLayout& b) noexcept
{

	std::swap(a.device, b.device);
	std::swap(a.layout, b.layout);
}
