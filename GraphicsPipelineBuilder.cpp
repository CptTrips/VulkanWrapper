#include "GraphicsPipelineBuilder.h"

GraphicsPipelineBuilder::GraphicsPipelineBuilder(Device& device)
    : device(device.vk())
{
}
