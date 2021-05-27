#pragma once

#include <string>

#include <GL/glew.h>

#include "glm/glm.hpp"

class Shader
{
public:

	/**
	 * Create a new OpenGL shader program.
	 *
	 * @param vertexFilePath Path to the vertex shader file.
	 * @param fragmentFilePath Path to the fragment shader file.
	 */
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	~Shader();

	/**
	 * Bind this shader.
	 */
	inline void Bind()
	{
		glUseProgram(m_RendererID);
	}

	/**
	 * Unbind this shader.
	 */
	inline void Unbind()
	{
		glUseProgram(0);
	}

	/**
	 * Set uniform of type bool.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetBool(const std::string& name, bool value);

	/**
	 * Set uniform of type float.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetFloat(const std::string& name, float value);

	/**
	 * Set uniform of type vec2.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetVec2(const std::string& name, const glm::vec2 value);

	/**
	 * Set uniform of type vec3.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetVec3(const std::string& name, const glm::vec3 value);

	/**
	 * Set uniform of type vec4.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetVec4(const std::string& name, const glm::vec4 value);

	/**
	 * Set uniform of type int.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetInt(const std::string& name, int32_t value);

	/**
	 * Set uniform of type unsigned int.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetUInt(const std::string& name, uint32_t value);

	/**
	 * Set uniform of type mat3.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetMat3(const std::string& name, const glm::mat3 value);

	/**
	 * Set uniform of type mat4.
	 *
	 * @param name Uniform's name.
	 * @param value Value to set.
	 */
	void SetMat4(const std::string& name, const glm::mat4 value);

private:
	
	/**
	 * Helper function to compile shader.
	 *
	 * @param type Type of shader (vertex, fragment, etc...).
	 * @param source String with shader's source code.
	 *
	 * @return OpenGL ID of the shader.
	 */
	uint32_t CompileShader(uint32_t type, const std::string& source);

	/**
	 * Get location for a uniform.
	 * This function handles location caching for better performance.
	 *
	 * @param name Uniform name.
	 */
	int32_t GetUniformLocation(const std::string& name);

private:
	
	uint32_t m_RendererID;

	std::unordered_map<std::string, int32_t> m_UniformLocationCache;
};
