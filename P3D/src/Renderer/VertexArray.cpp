#include "pch.h"

#include "VertexArray.h"

#include <GL/glew.h>

#include "BufferLayout.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

static GLenum ShaderDataTypeToGLType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:		return GL_INT;
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:		return GL_FLOAT;
		case ShaderDataType::Bool:		return GL_BOOL;
	}

	return 0;
}

VertexArray::VertexArray()
	: m_VertexAttribIndex(0)
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	glBindVertexArray(m_RendererID);

	vertexBuffer->Bind();

	const auto& layout = vertexBuffer->GetLayout();
	const auto& elements = layout.GetElements();

	for (auto& element : elements)
	{
		glVertexAttribPointer(
			m_VertexAttribIndex,
			element.ComponentCount,
			ShaderDataTypeToGLType(element.Type),
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(),
			(const void*)(intptr_t)element.Offset
		);

		glEnableVertexAttribArray(m_VertexAttribIndex++);
	}

	m_VertexBuffers.push_back(vertexBuffer);

	glBindVertexArray(0);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);

	indexBuffer->Bind();

	m_IndexBuffer = indexBuffer;

	glBindVertexArray(0);
}
