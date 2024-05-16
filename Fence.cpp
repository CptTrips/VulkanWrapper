#include "Fence.h"

#include <stdexcept>

Fence::Fence(VkDevice device)
    : device(device)
{

	VkFenceCreateInfo fenceInfo{};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if (vkCreateFence(this->device, &fenceInfo, nullptr, &fence) != VK_SUCCESS) 
        throw std::runtime_error("failed to create synchronization objects for a frame!");
}

Fence::Fence(Fence&& other) noexcept
    : device(other.device)
    , fence(VK_NULL_HANDLE)
{

    swap(other, *this);
}

Fence& Fence::operator=(Fence&& other) noexcept
{

    swap(other, *this);

    return *this;
}

Fence::~Fence()
{

    vkDestroyFence(device, fence, nullptr);
}

void Fence::wait(uint64_t timeout) const
{

	vkWaitForFences(device, 1, &fence, VK_TRUE, timeout);
}

void Fence::reset() const
{

    vkResetFences(device, 1, &fence);
}

VkFence Fence::vk() const
{

    return fence;
}

void swap(Fence& a, Fence& b) noexcept
{

    std::swap(a.device, b.device);
    std::swap(a.fence, b.fence);
}
