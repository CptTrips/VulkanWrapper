#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"

class Semaphore
{

    VkDevice device;

    VkSemaphore semaphore;

public:
    Semaphore(const Device& device);

    Semaphore(const Semaphore& other) = delete;

    Semaphore& operator=(const Semaphore& other) = delete;

    Semaphore(Semaphore&&) noexcept;

    Semaphore& operator=(Semaphore&&) noexcept;

    ~Semaphore();

    VkSemaphore vk() const;
};

