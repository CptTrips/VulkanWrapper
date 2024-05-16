#pragma once

#include <vulkan/vulkan.h>

class Semaphore
{

    VkDevice device;

    VkSemaphore semaphore;

public:
    Semaphore(VkDevice device);

    Semaphore(const Semaphore& other) = delete;

    Semaphore& operator=(const Semaphore& other) = delete;

    Semaphore(Semaphore&&) noexcept;

    Semaphore& operator=(Semaphore&&) noexcept;

    ~Semaphore();

    VkSemaphore vk() const;
};

