#include "Semaphore.h"

#include <stdexcept>

Semaphore::Semaphore(const Device& device)
    : device(device.vk())
{

    VkSemaphoreCreateInfo createInfo{};

    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    if (vkCreateSemaphore(device.vk(), &createInfo, nullptr, &semaphore) != VK_SUCCESS)
        throw std::runtime_error("Failed to create semaphore");
}

Semaphore::Semaphore(Semaphore&& other) noexcept
    : device(other.device)
    , semaphore(VK_NULL_HANDLE)
{

    std::swap(semaphore, other.semaphore);
}

Semaphore& Semaphore::operator=(Semaphore&& other) noexcept
{

    std::swap(semaphore, other.semaphore);

    return *this;
}

Semaphore::~Semaphore()
{

    vkDestroySemaphore(device, semaphore, nullptr);
}

VkSemaphore Semaphore::vk() const
{

    return semaphore;
}
