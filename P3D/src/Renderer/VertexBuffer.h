#pragma once

#include <GL/glew.h>

#include "BufferLayout.h"

class VertexBuffer
{
public:

	/**
	 * Create an vertex buffer.
	 *
	 * @param data Array with data to send to vertex buffer.
	 * @param size Number of elements in the array.
	 */
	VertexBuffer(float* data, uint32_t size);
	
	~VertexBuffer();

	/**
	 * Bind this vertex buffer.
	 */
	inline void Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	/**
	 * Unbind this vertex buffer.
	 */
	inline void Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	/**
	 * Get layout for this vertex buffer.
	 *
	 * @return BufferLayout object.
	 */
	inline const BufferLayout& GetLayout() const
	{
		return m_Layout;
	}

	/**
	 * Set layout for this vertex buffer.
	 *
	 * @param layout Layout you want to set.
	 */
	inline void SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

private:

	uint32_t m_RendererID;
	BufferLayout m_Layout;

};
