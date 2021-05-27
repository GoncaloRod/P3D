#pragma once

#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Renderer/BufferLayout.h"

struct Vertex
{
public:

	static BufferLayout GetBufferLayout()
	{
		return {
			{ ShaderDataType::Float3 },
			{ ShaderDataType::Float3 },
			{ ShaderDataType::Float2 },
		};
	}

	static constexpr uint32_t GetElementCount()
	{
		return 8;
	}
	
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textCoord;
};
