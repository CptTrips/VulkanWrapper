#include "Renderer.h"

#include <vulkan/vulkan.h>

#include <algorithm>

#include "CommandBuffer.h"
#include "Vertex.h"
#include "ShaderReader.h"


const std::vector<PipelineStage> Renderer::pipelineStages
{

	{VK_IMAGE_LAYOUT_UNDEFINED, 0, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT},
	{VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT},
	{VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ACCESS_2_NONE, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT}
};

Renderer::Renderer(RendererOptions options)
	: device(options.device)
	, QUEUE_SIZE(options.queueSize)
	, pipelineBarriers(createPipelineBarriers())
	, uiRenderer({ options.window, device, options.instance, options.swapChainFormat, options.swapChainSize })
	, vertexShader(options.vertexShader)
	, fragmentShader(options.fragmentShader)
	, graphicsPipeline(device, vertexShader, fragmentShader, options.swapChainFormat)
	, renderDomain{ options.swapChainExtent }
{

}

std::vector<PipelineBarrier> Renderer::createPipelineBarriers() const
{

	std::vector<PipelineBarrier> pipelineBarriers;

	PipelineStage prevStage{ pipelineStages[0] };

	for (auto it = pipelineStages.begin() + 1; it != pipelineStages.end(); it++)
	{

		pipelineBarriers.emplace_back(prevStage, *it);

		prevStage = *it;
	}

	return pipelineBarriers;
}

void Renderer::recordRenderCommands(CommandBuffer& commandBuffer, UI& ui, DeviceBuffer& vertexBuffer, DeviceBuffer& indexBuffer, const Image & image, const std::vector<DescriptorSet>& descriptorSets)
{

	pipelineBarriers[0].layoutTransition(commandBuffer, image);

	beginRendering(commandBuffer, image, VkRect2D{{0, 0}, renderDomain});

	uiRenderer.render(commandBuffer, ui);

	bindObjects(commandBuffer, vertexBuffer, indexBuffer);

	bindDescriptorSets(commandBuffer, descriptorSets);

	setDomain(commandBuffer, renderDomain);

	drawIndexed(commandBuffer, static_cast<uint32_t>(indexBuffer.size() / sizeof(uint32_t)));

	vkCmdEndRendering(commandBuffer.vk());

	pipelineBarriers[1].layoutTransition(commandBuffer, image);
}

void Renderer::bindDescriptorSets(CommandBuffer& commandBuffer, const std::vector<DescriptorSet>& descriptorSets)
{

	if (descriptorSets.empty())
		return;

	std::vector<VkDescriptorSet> descriptorSetsVk(descriptorSets.size());

	std::transform(descriptorSets.begin(), descriptorSets.end(), descriptorSetsVk.begin(), [](const DescriptorSet& descriptorSet) { return descriptorSet.vk();  });

	vkCmdBindDescriptorSets(commandBuffer.vk(), VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline.getLayout().vk(), 0, descriptorSetsVk.size(), descriptorSetsVk.data(), 0, nullptr);
}

void Renderer::beginRendering(CommandBuffer & commandBuffer, const Image & image, VkRect2D renderDomain) const
{

	VkRenderingAttachmentInfo colourAttachmentInfo{};
	
	colourAttachmentInfo.sType = VK_STRUCTURE_TYPE_RENDERING_ATTACHMENT_INFO;
	colourAttachmentInfo.imageView = image.getImageView();
	colourAttachmentInfo.imageLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	colourAttachmentInfo.resolveMode = VK_RESOLVE_MODE_NONE;
	colourAttachmentInfo.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colourAttachmentInfo.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colourAttachmentInfo.clearValue = { 0.0f, 0.0f, 0.0f, 1.0f };

	VkRenderingInfo renderInfo{};

	renderInfo.sType = VK_STRUCTURE_TYPE_RENDERING_INFO;
	renderInfo.renderArea = renderDomain;
	renderInfo.layerCount = 1;
	renderInfo.viewMask = 0;
	renderInfo.colorAttachmentCount = 1;
	renderInfo.pColorAttachments = &colourAttachmentInfo;
	renderInfo.pDepthAttachment = VK_NULL_HANDLE;
	renderInfo.pStencilAttachment = VK_NULL_HANDLE;
	
	vkCmdBeginRendering(commandBuffer.vk(), &renderInfo);

}

void Renderer::bindObjects(CommandBuffer& commandBuffer, DeviceBuffer& vertexBuffer, DeviceBuffer& indexBuffer) const
{

	graphicsPipeline.bind(commandBuffer);

    VkBuffer vertexBuffers[] = { vertexBuffer.vk() };

	VkDeviceSize offsets[] = { 0 };

	vkCmdBindVertexBuffers(commandBuffer.vk(), 0, 1, vertexBuffers, offsets);

	vkCmdBindIndexBuffer(commandBuffer.vk(), indexBuffer.vk(), 0, VK_INDEX_TYPE_UINT32);


}

void Renderer::setDomain(CommandBuffer& commandBuffer, VkExtent2D extent)
{

	VkViewport viewport{};
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float) extent.width;
	viewport.height = (float) extent.height;
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	vkCmdSetViewport(commandBuffer.vk(), 0, 1, &viewport);

	VkRect2D scissor{};
	scissor.offset = {0, 0};
	scissor.extent = extent;
	vkCmdSetScissor(commandBuffer.vk(), 0, 1, &scissor);
}

void Renderer::drawIndexed(CommandBuffer& commandBuffer, uint32_t indexCount) const
{

	int instanceCount = 1;
	int firstIndex = 0;
	int vertexOffset = 0;
	int firstInstance = 0;
	vkCmdDrawIndexed(commandBuffer.vk(), indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}
