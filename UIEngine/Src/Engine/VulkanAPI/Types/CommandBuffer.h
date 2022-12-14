#pragma once
#include "vulkan/vulkan.hpp"
#include <functional>

namespace vulkan
{
class CommandBuffer
{
public:
	CommandBuffer() = default;
	CommandBuffer(const vk::Device& device, const vk::CommandPool& commandPool, vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary);
	~CommandBuffer() = default;

	void Create(const vk::Device& device, const vk::CommandPool& commandPool, vk::CommandBufferLevel level = vk::CommandBufferLevel::ePrimary);
	void Destroy();

	// Helper functions
	void Begin(vk::CommandBufferUsageFlags flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit) const;
	void End() const;
	void Reset(vk::CommandBufferResetFlags flags = vk::CommandBufferResetFlagBits::eReleaseResources) const;

	// Record functions
	void BeginRenderPass(vk::RenderPass& renderPass, vk::Extent2D renderArea, vk::Framebuffer& framebuffer, vk::SubpassContents subpassContents = vk::SubpassContents::eInline) const;
	void NextSubpass(vk::SubpassContents subpassContents = vk::SubpassContents::eInline) const;
	void EndRenderPass() const;

	// Start recording then run lambda function then end recording
	void Record(vk::CommandBufferUsageFlags flags, std::function<void()> lambda) const;

	void BindPipeline(vk::PipelineBindPoint pipelineBindPoint, vk::Pipeline pipeline) const;
	void BindVertexBuffers(uint32_t firstBinding, vk::ArrayProxy<const vk::Buffer> buffers, vk::ArrayProxy<const vk::DeviceSize> offsets) const;
	void BindIndexBuffer(vk::Buffer buffer, vk::DeviceSize offset, vk::IndexType indexType) const;
	void BindDescriptorSets(vk::PipelineBindPoint pipelineBindPoint, vk::PipelineLayout layout, uint32_t firstSet, vk::ArrayProxy<const vk::DescriptorSet> descriptorSets, vk::ArrayProxy<const uint32_t> dynamicOffsets) const;

	void SetViewport(const vk::Extent2D& viewport) const;
	void SetScissor(const vk::Extent2D& scissor) const;

	void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const;
	void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) const;
	void DrawIndirect(vk::Buffer buffer, vk::DeviceSize offset, uint32_t drawCount, uint32_t stride) const;
	void DrawIndexedIndirect(vk::Buffer buffer, vk::DeviceSize offset, uint32_t drawCount, uint32_t stride) const;

	// Getters
	vk::CommandBuffer get() const
	{
		return m_CommandBuffer;
	}

	// Cast operator
	operator vk::CommandBuffer() const
	{
		return m_CommandBuffer;
	}

void RecordDummyCommands();

private:
	vk::CommandBuffer m_CommandBuffer;
};
} // namespace vulkan