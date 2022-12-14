#include "CommandBuffer.h"
namespace vulkan
{

CommandBuffer::CommandBuffer(const vk::Device& device, const vk::CommandPool& commandPool, vk::CommandBufferLevel level /*= ePrimary*/)
{
	Create(device, commandPool, level);
}

void CommandBuffer::Create(const vk::Device& device, const vk::CommandPool& commandPool, vk::CommandBufferLevel level /*= ePrimary*/)
{
	vk::CommandBufferAllocateInfo allocInfo = {};
	allocInfo.commandPool                   = commandPool;
	allocInfo.level                         = level;
	allocInfo.commandBufferCount            = 1;

	m_CommandBuffer = device.allocateCommandBuffers(allocInfo)[0];
}

void CommandBuffer::Destroy()
{
	m_CommandBuffer.reset();
}

void CommandBuffer::Begin(vk::CommandBufferUsageFlags flags /*= eOneTimeSubmit*/) const
{
	vk::CommandBufferBeginInfo beginInfo = {};
	beginInfo.flags                      = flags;
	m_CommandBuffer.begin(beginInfo);
}

void CommandBuffer::End() const
{
	m_CommandBuffer.end();
}

void CommandBuffer::Reset(vk::CommandBufferResetFlags flags /*= eReleaseResources*/) const
{
	m_CommandBuffer.reset(flags);
}

void CommandBuffer::BeginRenderPass(vk::RenderPass& renderPass, vk::Extent2D renderArea, vk::Framebuffer& framebuffer, vk::SubpassContents subpassContents /*= vk::SubpassContents::eInline*/) const
{
	vk::RenderPassBeginInfo renderPassInfo = {};
	renderPassInfo.renderPass              = renderPass;
	renderPassInfo.framebuffer             = framebuffer;
	renderPassInfo.renderArea.offset       = vk::Offset2D(0, 0);
	renderPassInfo.renderArea.extent       = renderArea;
	renderPassInfo.clearValueCount         = 1;
	
	// Maybe move this else where
	static std::array<float, 4> clearColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	vk::ClearValue clearValue;
	clearValue.color = vk::ClearColorValue(clearColor);
	renderPassInfo.pClearValues = &clearValue;
	
	m_CommandBuffer.beginRenderPass(renderPassInfo, subpassContents);
}

void CommandBuffer::NextSubpass(vk::SubpassContents subpassContents /*= eInline*/) const
{
	m_CommandBuffer.nextSubpass(subpassContents);
}

void CommandBuffer::EndRenderPass() const
{
	m_CommandBuffer.endRenderPass();
}

void CommandBuffer::Record(vk::CommandBufferUsageFlags flags, std::function<void()> lambda) const
{
	Begin(flags);
	lambda();
	End();
}

void CommandBuffer::BindPipeline(vk::PipelineBindPoint pipelineBindPoint, vk::Pipeline pipeline) const
{
	m_CommandBuffer.bindPipeline(pipelineBindPoint, pipeline);
}

void CommandBuffer::BindVertexBuffers(uint32_t firstBinding, vk::ArrayProxy<const vk::Buffer> buffers, vk::ArrayProxy<const vk::DeviceSize> offsets) const
{
	m_CommandBuffer.bindVertexBuffers(firstBinding, buffers, offsets);
}

void CommandBuffer::BindIndexBuffer(vk::Buffer buffer, vk::DeviceSize offset, vk::IndexType indexType) const
{
	m_CommandBuffer.bindIndexBuffer(buffer, offset, indexType);
}

void CommandBuffer::BindDescriptorSets(vk::PipelineBindPoint pipelineBindPoint, vk::PipelineLayout layout, uint32_t firstSet, vk::ArrayProxy<const vk::DescriptorSet> descriptorSets,
									   vk::ArrayProxy<const uint32_t> dynamicOffsets) const
{
	m_CommandBuffer.bindDescriptorSets(pipelineBindPoint, layout, firstSet, descriptorSets, dynamicOffsets);
}

void CommandBuffer::SetViewport(const vk::Extent2D& viewport) const
{
	vk::Viewport viewportInfo = {};
	viewportInfo.x            = 0.0f;
	viewportInfo.y            = 0.0f;
	viewportInfo.width        = static_cast<float>(viewport.width);
	viewportInfo.height       = static_cast<float>(viewport.height);
	viewportInfo.minDepth     = 0.0f;
	viewportInfo.maxDepth     = 1.0f;
	m_CommandBuffer.setViewport(0, 1, &viewportInfo);
}

void CommandBuffer::SetScissor(const vk::Extent2D& scissor) const
{
	vk::Rect2D scissorInfo = {};
	scissorInfo.offset     = vk::Offset2D(0, 0);
	scissorInfo.extent     = scissor;
	m_CommandBuffer.setScissor(0, 1, &scissorInfo);
}

void CommandBuffer::Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const
{
	m_CommandBuffer.draw(vertexCount, instanceCount, firstVertex, firstInstance);
}

void CommandBuffer::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const
{
	m_CommandBuffer.drawIndexed(indexCount, instanceCount, firstIndex, vertexOffset, firstInstance);
}

void CommandBuffer::DrawIndirect(vk::Buffer buffer, vk::DeviceSize offset, uint32_t drawCount, uint32_t stride) const
{
	m_CommandBuffer.drawIndirect(buffer, offset, drawCount, stride);
}

void CommandBuffer::DrawIndexedIndirect(vk::Buffer buffer, vk::DeviceSize offset, uint32_t drawCount, uint32_t stride) const
{
	m_CommandBuffer.drawIndexedIndirect(buffer, offset, drawCount, stride);
}

void CommandBuffer::RecordDummyCommands()
{
	Begin(vk::CommandBufferUsageFlagBits::eOneTimeSubmit);
	End();
}

} // namespace vulkan