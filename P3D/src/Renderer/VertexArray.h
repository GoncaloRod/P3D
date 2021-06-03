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

	/**
	 * Assign a vertex buffer to this vertex array.
	 *
	 * @param vertexBuffer Pointer to the vertex buffer to assign.
	 */
	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);

	/**
	 * Set an index buffer to this vertex array.
	 *
	 * @param indexBuffer Pointer to the index buffer to assign.
	 */
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	/**
	 * Get every vertex buffer assign to this vertex array.
	 *
	 * @return Vector with pointers to assigned vertex arrays.
	 */
	inline const std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}

	/**
	 * Get index buffer assigned to this vertex array.
	 *
	 * @return Pointer to assigned index buffer.
	 */
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