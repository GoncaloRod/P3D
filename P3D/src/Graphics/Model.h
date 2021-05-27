#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/transform.hpp"

class Mesh;
class Material;
class Shader;

class Model
{
public:

	Model(const std::vector<std::shared_ptr<Mesh>>& meshes, const std::unordered_map<std::string, std::shared_ptr<Material>>& materials, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));
	~Model() = default;

	void Draw() const;

	constexpr glm::vec3 GetPosition() const
	{
		return m_Position;
	}

	constexpr glm::vec3 GetRotation() const
	{
		return m_Rotation;
	}

	constexpr glm::vec3 GetScale() const
	{
		return m_Scale;
	}

	inline void SetPosition(glm::vec3 position)
	{
		m_Position = position;

		UpdateModelMat();
	}

	inline void SetRotation(glm::vec3 rotation)
	{
		m_Rotation = rotation;

		UpdateModelMat();
	}

	inline void SetScale(glm::vec3 scale)
	{
		m_Scale = scale;

		UpdateModelMat();
	}

	static Model* LoadFromObj(std::shared_ptr<Shader> pShader, const std::string& filePath, glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1));

private:

	inline void UpdateModelMat()
	{
		m_ModelMat = glm::mat4(1.0f);
		
		m_ModelMat = glm::translate(m_ModelMat, m_Position);	
		m_ModelMat = glm::scale(m_ModelMat, m_Scale);
	
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_ModelMat = glm::rotate(m_ModelMat, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	std::vector<std::shared_ptr<Mesh>> m_Meshes;
	std::unordered_map<std::string, std::shared_ptr<Material>> m_Materials;

	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	glm::mat4 m_ModelMat;
};
