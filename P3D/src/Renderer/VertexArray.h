#pragma once

#include <vector>
#include <memory>

#include <GL/glew.h>

#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray
{
public:

	VertexArray();
	~VertexArray();

	/**
	 * Bind this vertex array.
	 */
	inline void Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	/**
	 * Unbind this vertex array.
	 */
	inline void Unbind() const
	{
		glBindVertexArray(0);
	}

	
	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	inline const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	inline const std::shared_ptr<IndexBuffer> GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

private:

	uint32_t m_RendererID;
	uint32_t m_VertexAttribIndex;

	std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	
};