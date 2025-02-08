#pragma once

#include "GLFWWindow.h"
#include "VulkanInstance.h"
#include "Device.h"
#include "Surface.h"

class VulkanContext
{

    static const std::vector<const char*> layers;
    static const std::vector<const char*> deviceExtensions;

public:
    VulkanContext(uint32_t windowHeight, uint32_t windowWidth);

    GLFWWindow window;

    VulkanInstance instance;

    Surface surface;

    Device device;

};

