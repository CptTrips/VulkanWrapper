#pragma once

#include "DeviceBuffer.h"

struct ShaderResource
{

    DeviceBuffer& buffer;

    VkDescriptorSetLayoutBinding binding;
};

