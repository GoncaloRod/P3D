#pragma once

#include <vector>

enum class ShaderDataType
{
	Int, Int2, Int3, Int4,
	Float, Float2, Float3, Float4,
	Bool,
	Mat3, Mat4
};

/**
 * Get the number of components from a shader data type.
 *
 * @return Number of components.
 */
static uint32_t GetShaderDataTypeComponentCount(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Int:
		case ShaderDataType::Float:
		case ShaderDataType::Bool:		return 1;

		case ShaderDataType::Int2:
		case ShaderDataType::Float2:	return 2;

		case ShaderDataType::Int3:
		case ShaderDataType::Float3:	return 3;

		case ShaderDataType::Int4:
		case ShaderDataType::Float4:	return 4;

		case ShaderDataType::Mat3:		return 3 * 3;

		case ShaderDataType::Mat4:		return 4 * 4;
	}

	return 0;
}

/**
 * Get the size in bytes from a shader data type.
 *
 * @return Size in bytes.
 */
static uint32_t GetShaderDataTypeSize(ShaderDataType Type)
{
	switch (Type)
	{
		case ShaderDataType::Bool:		return 1;

		case ShaderDataType::Int:
		case ShaderDataType::Float:		return 4;

		case ShaderDataType::Int2:
		case ShaderDataType::Float2:	return 4 * 2;

		case ShaderDataType::Int3:
		case ShaderDataType::Float3:	return 4 * 3;

		case ShaderDataType::Int4:
		case ShaderDataType::Float4:	return 4 * 4;

		case ShaderDataType::Mat3:		return 4 * 3 * 3;

		case ShaderDataType::Mat4:		return 4 * 4 * 4;
	}

	return 0;
}

struct BufferElement
{
	ShaderDataType Type;
	bool Normalized;
	uint32_t ComponentCount;
	uint32_t Size;
	uint32_t Offset;

	/**
	 * Create a new buffer layout element.
	 *
	 * @param type Data type of the parameter.
	 * @param normalized Whether or not it needs to be normalized (false by default).
	 */
	BufferElement(ShaderDataType type, bool normalized = false)
		: Type(type), Normalized(normalized), Offset(0)
	{
		ComponentCount = GetShaderDataTypeComponentCount(Type);
		Size = GetShaderDataTypeSize(Type);
	}
};

class BufferLayout
{
public:

	BufferLayout() = default;
	~BufferLayout() = default;

	/**
	 * Create a new vertex buffer layout.
	 *
	 * @param elements Elements that make the buffer layout.
	 */
	BufferLayout(std::initializer_list<BufferElement> elements)
		: m_Elements(elements), m_Stride(0)
	{
		// Calculate offsets and stride
		for (auto& element : m_Elements)
		{
			element.Offset = m_Stride;
			m_Stride += element.Size;
		}
	}

	/**
	 * Get a vector with all the elements in this layout.
	 *
	 * @return Vector with elements.
	 */
	inline const std::vector<BufferElement>& GetElements() const
	{
		return m_Elements;
	}

	/**
	 * Stride value for this layout.
	 *
	 * @return Unsigned integer with stride value.
	 */
	inline uint32_t GetStride() const
	{
		return m_Stride;
	}

private:

	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride;

};