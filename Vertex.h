#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include <vulkan\vulkan.h>
#include <array>

using glm::vec2;
using glm::vec3;

using std::array;

struct Vertex
{

	vec3 pos;
	vec3 color;
	vec2 texCoord;

	static VkVertexInputBindingDescription getBindingDescription();
	static array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions();

    bool operator==(const Vertex& other) const;
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<vec3>()(vertex.pos) ^
                   (hash<vec3>()(vertex.color) << 1)) >> 1) ^
                   (hash<vec2>()(vertex.texCoord) << 1);
        }
    };
}
