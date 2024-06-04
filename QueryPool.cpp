#include "QueryPool.h"

QueryPool::QueryPool(VkDevice device, VkQueryType type, uint32_t count)
    : device(device)
    , pool(VK_NULL_HANDLE)
    , count(count)
{

    VkQueryPoolCreateInfo info{};

    info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;

    info.queryCount = count;
    info.queryType = type;

    vkCreateQueryPool(device, &info, nullptr, &pool);
}

QueryPool::~QueryPool()
{

    vkDestroyQueryPool(device, pool, nullptr);
}

VkQueryPool QueryPool::vk() const
{
    return pool;
}

