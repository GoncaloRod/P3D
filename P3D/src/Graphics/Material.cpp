#include "pch.h"

#include "Material.h"

#include "Renderer/Shader.h"
#include "Renderer/Texture2D.h"

Material::Material(std::shared_ptr<Shader> pShader)
    : m_pShader(pShader), m_DiffuseColor(1.0f), m_EmissiveColor(0.0f), m_SpecularColor(1.0f), m_SpecularExponent(1.0f)
{
}

Material::Material(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture2D> pDiffuseMap)
	: m_pShader(pShader), m_pDiffuseMap(pDiffuseMap), m_DiffuseColor(1.0f), m_EmissiveColor(0.0f), m_SpecularColor(1.0f), m_SpecularExponent(1.0f)
{
}

Material::Material(std::shared_ptr<Shader> pShader, std::shared_ptr<Texture2D> pDiffuseMap, std::shared_ptr<Texture2D> pEmissiveMap)
	: m_pShader(pShader), m_pDiffuseMap(pDiffuseMap), m_pEmissiveMap(pEmissiveMap), m_DiffuseColor(1.0f), m_EmissiveColor(0.0f), m_SpecularColor(1.0f), m_SpecularExponent(1.0f)
{
}

void Material::Bind() const
{
	m_pShader->Bind();

	m_pShader->SetVec3("u_Material.DiffuseColor", m_DiffuseColor);
	m_pShader->SetVec3("u_Material.EmissiveColor", m_EmissiveColor);
	m_pShader->SetVec3("u_Material.SpecularColor", m_SpecularColor);
	m_pShader->SetFloat("u_Material.SpecularExponent", m_SpecularExponent);
	
    if (m_pDiffuseMap.get() != nullptr)
    {
	    m_pDiffuseMap->Bind();
    	m_pShader->SetInt("u_Material.DiffuseMap", 0);
    	m_pShader->SetBool("u_Material.HasDiffuseMap", true);
    }
	else
	{
		m_pShader->SetBool("u_Material.HasDiffuseMap", false);
	}

	if (m_pEmissiveMap.get() != nullptr)
	{
		m_pEmissiveMap->Bind(1);
		m_pShader->SetInt("u_Material.EmissiveMap", 1);
		m_pShader->SetBool("u_Material.HasEmissiveMap", true);
	}
	else
	{
		m_pShader->SetBool("u_Material.HasEmissiveMap", false);
	}

	if (m_pNormalMap.get() != nullptr)
	{
		m_pNormalMap->Bind(2);
		m_pShader->SetInt("u_Material.NormalMap", 2);
		m_pShader->SetBool("u_Material.HasNormalMap", true);
	}
	else
	{
		m_pShader->SetBool("u_Material.HasNormalMap", false);
	}
}

std::unordered_map<std::string, std::shared_ptr<Material>> Material::LoadFromMtl(std::shared_ptr<Shader> pShader, const std::string& filePath)
{
	std::unordered_map<std::string, std::shared_ptr<Material>> materials;
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cout << "Failed to open '" << filePath << "'";
	}

	std::string directory;
	const auto lastSlashIdX = filePath.rfind('/');
	if (std::string::npos != lastSlashIdX)
	{
		directory = filePath.substr(0, lastSlashIdX);
	}

	std::stringstream stream;
	std::string line;
	std::string prefix;

	std::shared_ptr<Material> selectedMat;
	
	while (std::getline(file, line))
	{
		stream.clear();
		stream.str(line);
		stream >> prefix;

		if (prefix == "newmtl")
		{
			std::string matName;
			stream >> matName;
			
			selectedMat = materials[matName] = std::make_shared<Material>(pShader);
		}
		else if (prefix == "Kd")
		{
			glm::vec3 color;
			stream >> color.r >> color.g >> color.b;
			selectedMat->SetDiffuseColor(color);
		}
		else if (prefix == "Ke")
		{
			glm::vec3 color;
			stream >> color.r >> color.g >> color.b;
			selectedMat->SetSpecularColor(color);
		}
		else if (prefix == "Ks")
		{
			glm::vec3 color;
			stream >> color.r >> color.g >> color.b;
			selectedMat->SetSpecularColor(color);
		}
		else if (prefix == "Ns")
		{
			float exponent;
			stream >> exponent;
			selectedMat->SetSpecularExponent(exponent);
		}
		else if (prefix == "map_Kd")
		{
			std::string textFileName;
			stream >> textFileName;
			selectedMat->SetDiffuseMap(std::make_shared<Texture2D>(directory + '/' + textFileName));
		}
		else if (prefix == "map_Ke")
		{
			std::string textFileName;
			stream >> textFileName;
			selectedMat->SetEmissiveMap(std::make_shared<Texture2D>(directory + '/' + textFileName));
		}
		else if (prefix == "map_Bump")
		{
			std::string textFileName;
			stream >> textFileName;
			selectedMat->SetNormalMap(std::make_shared<Texture2D>(directory + '/' + textFileName));
		}
	}

	return materials;
}
