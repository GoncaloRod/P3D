#pragma once

#include "glm/vec3.hpp"

class Texture2D;
class Shader;

class Material
{
public:

	Material(std::shared_ptr<Shader> pShader);
	Material(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture2D> pDiffuseMap);
	Material(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture2D> pDiffuseMap, std::shared_ptr<Texture2D> pEmissiveMap);
	~Material() = default;

	void Bind() const;

	inline std::shared_ptr<Shader> GetShader() const
	{
		return m_pShader;
	}

	inline std::shared_ptr<Texture2D> GetDiffuseMap() const
	{
		return m_pDiffuseMap;
	}

	inline std::shared_ptr<Texture2D> GetEmissiveMap() const
	{
		return m_pEmissiveMap;
	}

	inline std::shared_ptr<Texture2D> GetNormalMap() const
	{
		return m_pNormalMap;
	}

	constexpr glm::vec3 GetDiffuseColor() const
	{
		return m_DiffuseColor;
	}

	constexpr glm::vec3 GetSpecularColor() const
	{
		return m_SpecularColor;
	}

	constexpr float GetSpecularExponent() const
	{
		return m_SpecularExponent;
	}

	inline void SetDiffuseMap(std::shared_ptr<Texture2D> texture)
	{
		m_pDiffuseMap = texture;
	}

	inline void SetEmissiveMap(std::shared_ptr<Texture2D> texture)
	{
		m_pEmissiveMap = texture;
	}

	inline void SetNormalMap(std::shared_ptr<Texture2D> texture)
	{
		m_pNormalMap = texture;
	}

	inline void SetDiffuseColor(glm::vec3 diffuseColor)
	{
		m_DiffuseColor = diffuseColor;
	}

	inline void SetSpecularColor(glm::vec3 specularColor)
	{
		m_SpecularColor = specularColor;
	}

	inline void SetSpecularExponent(float specularExponent)
	{
		m_SpecularExponent = specularExponent;
	}

	static std::unordered_map<std::string, std::shared_ptr<Material>> LoadFromMtl(std::shared_ptr<Shader> pShader, const std::string& filePath);

private:

	std::shared_ptr<Shader> m_pShader;
	
	std::shared_ptr<Texture2D> m_pDiffuseMap;
	std::shared_ptr<Texture2D> m_pEmissiveMap;
	std::shared_ptr<Texture2D> m_pNormalMap;

	glm::vec3 m_DiffuseColor;
	glm::vec3 m_EmissiveColor;
	glm::vec3 m_SpecularColor;
	float m_SpecularExponent;
};
