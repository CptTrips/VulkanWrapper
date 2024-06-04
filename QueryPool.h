#pragma once

#include <vulkan\vulkan.h>

class QueryPool
{

    constexpr static uint32_t MAX_QUERIES{ 1024 };

    VkDevice device;

    VkQueryPool pool;

    uint32_t count;


public:
    QueryPool(VkDevice device, VkQueryType type, uint32_t count = MAX_QUERIES);

    QueryPool(const QueryPool&) = delete;

    QueryPool& operator=(const QueryPool&) = delete;

    ~QueryPool();

    VkQueryPool vk() const;

    template <typename T>
    T getResult(uint32_t query, VkQueryResultFlags flags = VK_QUERY_RESULT_WAIT_BIT) const;
};

template<typename T>
inline T QueryPool::getResult(uint32_t query, VkQueryResultFlags flags) const
{
    T result;

    vkGetQueryPoolResults(device, pool, query, 1, sizeof(result), &result, sizeof(result), flags);

    return result;
}
