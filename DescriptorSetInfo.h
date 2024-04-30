#pragma once

#include <vector>
#include "DescriptorSetLayout.h"
#include "Descriptor.h"

struct DescriptorSetInfo
{

    std::vector<Descriptor> descriptors;

    const DescriptorSetLayout* descriptorSetLayout;

    DescriptorSetInfo(std::vector<Descriptor> descriptors, const DescriptorSetLayout* descriptorSetLayout)
        : descriptors(descriptors)
        , descriptorSetLayout(descriptorSetLayout)
    {}
};

