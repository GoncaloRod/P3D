#include "pch.h"

#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(float* data, uint32_t size)
{
	// WARNING: With OpenGL 4.5 or newer use 'glCreateBuffers'
	glGenBuffers(1, &m_RendererID);

	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}
