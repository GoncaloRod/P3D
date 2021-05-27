#pragma once

#include <GL/glew.h>

class IndexBuffer
{
public:

	/**
	 * Create an index buffer.
	 *
	 * @param indices Array of indices for this index buffer.
	 * @param count Number of indices in the array.
	 */
	IndexBuffer(uint32_t* indices, uint32_t count);

	~IndexBuffer();

	/**
	 * Bind this index buffer.
	 */
	inline void Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	/**
	 * Unbind this index buffer.
	 */
	inline void Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	/**
	 * Get number of indices in this index buffer.
	 *
	 * @return Number of indices in this index buffer.
	 */
	inline uint32_t GetCount() const
	{
		return m_Count;
	}

private:

	uint32_t m_RendererID;
	uint32_t m_Count;

};