#pragma once

#include <GL/glew.h>

class Texture2D
{
public:

	Texture2D(const std::string& filePath);
	~Texture2D();

	inline void Bind(uint32_t slot = 0) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	
	inline void Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:

	uint32_t m_RendererID;

	std::string m_FilePath;
	int32_t m_Width, m_Height, m_Channels;
	uint8_t* m_LocalBuffer;
};
