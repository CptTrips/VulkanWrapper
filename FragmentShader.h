#pragma once

#include <string>
#include <vector>

#include <vulkan/vulkan.h>

#include "Device.h"
#include "Shader.h"

class FragmentShader : public Shader
{

public:
    FragmentShader(
        const Device& device,
        const std::vector<char>& code,
        const std::vector<VkDescriptorSetLayoutBinding>& bindings,
        const std::vector<VkPushConstantRange>& pushConstantRanges
    );
    
};

