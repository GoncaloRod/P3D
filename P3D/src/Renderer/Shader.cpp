#include "pch.h"

#include "Shader.h"

static std::string ReadFile(const std::string& filePath)
{
	std::string result;
	std::ifstream in(filePath, std::ios::in);

	if (in)
	{
		// Calculate file's string size
		in.seekg(0, std::ios::end);
		result.resize((size_t)in.tellg());
		in.seekg(0, std::ios::beg);

		in.read(&result[0], result.size());

		in.close();
	}
	else
	{
		std::cout << "Failed to open file '" << filePath << "'" << std::endl;
	}

	return result;
}

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	int success;
	char message[512];

	// Read shaders source from files
	std::string vertexSource = ReadFile(vertexFilePath);
	std::string fragmentSource = ReadFile(fragmentFilePath);

	// Compile shaders
	uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
	uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	// Create shader program
	m_RendererID = glCreateProgram();

	// Attach shaders to program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);

	// Link program and check for linking errors
	glLinkProgram(m_RendererID);

	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);

	if (!success)
	{
		// Linking failed!
		// Get error message and print it to the screen
		glGetProgramInfoLog(m_RendererID, sizeof(message), nullptr, message);

		std::cout << "Shader program linking failed:\n" << message << std::endl;
	}

	glValidateProgram(m_RendererID);

	// Delete unnecessary shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
	uint32_t shader = glCreateShader(type);
	const char* sourceStr = source.c_str();
	int success;
	char message[512];
	
	// Compile
	glShaderSource(shader, 1, &sourceStr, nullptr);
	glCompileShader(shader);

	// Check for compile errors
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// Compilation failed!
		// Get error message, print it to the screen and delete shader
		glGetShaderInfoLog(shader, sizeof(message), nullptr, message);

		std::cout << "Shader compilation error:\n" << message << std::endl;

		glDeleteShader(shader);

		return 0;
	}

	return shader;
}

void Shader::SetBool(const std::string& name, bool value)
{
	glUniform1i(GetUniformLocation(name), static_cast<int>(value));
}

void Shader::SetFloat(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec2(const std::string& name, const glm::vec2 value)
{
	glUniform2fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetVec3(const std::string& name, const glm::vec3 value)
{
	glUniform3fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetVec4(const std::string& name, const glm::vec4 value)
{
	glUniform4fv(GetUniformLocation(name), 1, &value[0]);
}

void Shader::SetInt(const std::string& name, int32_t value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUInt(const std::string& name, uint32_t value)
{
	glUniform1ui(GetUniformLocation(name), value);
}

void Shader::SetMat3(const std::string& name, const glm::mat3 value)
{
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

void Shader::SetMat4(const std::string& name, const glm::mat4 value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}

int32_t Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		// Location in cache, just return it
		return m_UniformLocationCache[name];
	}

	// Location is not in cache, find it
	int32_t location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
		std::cout << "Failed to find uniform named '" << name << "'" << std::endl;

	m_UniformLocationCache[name] = location;

	return location;
}
