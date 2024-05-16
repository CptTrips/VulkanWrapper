#pragma once

#include "CommandBuffer.h"
#include "GLFWWindow.h"
#include "Device.h"
#include "VulkanInstance.h"
#include "SwapChain.h"
#include "UI.h"
#include "DescriptorPool.h"


struct UIRendererOptions
{

    const GLFWWindow& window;
    const Device& device;
    const VulkanInstance& instance;
    VkFormat swapChainFormat;
    uint32_t swapChainSize;

    UIRendererOptions(
        const GLFWWindow& window,
        const Device& device,
        const VulkanInstance& instance,
        VkFormat swapChainFormat,
        uint32_t swapChainSize
    )
        : window(window)
        , device(device)
        , instance(instance)
        , swapChainFormat(swapChainFormat)
        , swapChainSize(swapChainSize)
    {}
};


class UIRenderer
{

    static const std::unordered_set<VkDescriptorType> requiredDescriptorTypes;
    DescriptorPool descriptorPool;

public:
    UIRenderer(const UIRendererOptions& options);

    void render(CommandBuffer& commandBuffer, UI& ui);

    ~UIRenderer();
};

