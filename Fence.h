#pragma once

#include <vulkan\vulkan.h>

class Fence
{

    VkFence fence;

    VkDevice device;

public:

    Fence(VkDevice device);

    friend void swap(Fence& a, Fence& b) noexcept;

    Fence(const Fence&) = delete;

    Fence(Fence&&) noexcept;

    Fence& operator=(const Fence&) = delete;

    Fence& operator=(Fence&&) noexcept;

    ~Fence();

    void wait(uint64_t timeout = UINT64_MAX) const;

    void reset() const;

    VkFence vk() const;
};

