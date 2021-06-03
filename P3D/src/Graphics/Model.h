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

	/**
	 * Draw this model.
	 */
	void Draw() const;

	/**
	 * Get model's position.
	 *
	 * @return 3 dimensional vector with model's position.
	 */
	constexpr glm::vec3 GetPosition() const
	{
		return m_Position;
	}

	/**
	 * Get model's rotation.
	 *
	 * @return 3 dimensional vector with model's rotation.
	 */
	constexpr glm::vec3 GetRotation() const
	{
		return m_Rotation;
	}

	/**
	 * Get model's scale.
	 *
	 * @return 3 dimensional vector with model's scale.
	 */
	constexpr glm::vec3 GetScale() const
	{
		return m_Scale;
	}

	/**
	 * Set a new position for model.
	 *
	 * @param position Model's new position.
	 */
	inline void SetPosition(glm::vec3 position)
	{
		m_Position = position;

		UpdateModelMat();
	}

	/**
	 * Set a new rotation for model.
	 *
	 * @param rotation Model's new rotation.
	 */
	inline void SetRotation(glm::vec3 rotation)
	{
		m_Rotation = rotation;

		UpdateModelMat();
	}

	/**
	 * Set a new scale for model.
	 *
	 * @param scale Model's new scale.
	 */
	inline void SetScale(glm::vec3 scale)
	{
		m_Scale = scale;

		UpdateModelMat();
	}

	/**
	 * Load model from .obj file.
	 *
	 * @param pShader Pointer to the shader to be used by model's materials.
	 * @param filePath Path to the .obj file.
	 * @param position Model's stating position. Defaults to (0, 0, 0).
	 * @param rotation Model's stating rotation. Defaults to (0, 0, 0).
	 * @param scale Model's stating scale. Defaults to (1, 1, 1).
	 *
	 * @return Pointer to the loaded model.
	 */
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
