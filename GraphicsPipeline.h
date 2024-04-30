#pragma once

#include <vulkan/vulkan.h>

#include "Device.h"
#include "PipelineLayout.h"
#include "CommandBuffer.h"
#include "Shader.h"
#include "VertexShader.h"

class GraphicsPipeline
{

    VkDevice device;

    VkPipeline pipeline;

    PipelineLayout pipelineLayout;

    template <typename T>
    static std::vector<T> concatVectors(const std::vector<T>& a, const std::vector<T>& b);

public:
    GraphicsPipeline(Device& device, VkFormat colourFormat, VertexShader& vertexShader, Shader& fragmentShader);

    ~GraphicsPipeline();

    void bind(CommandBuffer& commandBuffer) const;
};

template<typename T>
inline std::vector<T> GraphicsPipeline::concatVectors(const std::vector<T>& a, const std::vector<T>& b)
{

    std::vector<T> result{ a };

    for (const T& elem : b)
        result.push_back(elem);

    return result;
}
