#include "pch.h"

#include "Model.h"

#include "Mesh.h"
#include "Material.h"
#include "glm/gtx/transform.hpp"

Model::Model(const std::vector<std::shared_ptr<Mesh>>& meshes, const std::unordered_map<std::string, std::shared_ptr<Material>>& materials, glm::vec3 position /* = 0 */, glm::vec3 rotation /* = 0 */, glm::vec3 scale /* = 0 */)
	: m_Meshes(meshes), m_Materials(materials), m_Position(position), m_Rotation(rotation), m_Scale(scale)
{
	UpdateModelMat();
}


void Model::Draw() const
{
	for (const auto pMesh : m_Meshes)
	{
		pMesh->Draw(m_ModelMat);
	}
}

Model* Model::LoadFromObj(std::shared_ptr<Shader> pShader, const std::string& filePath, glm::vec3 position /* = 0 */, glm::vec3 rotation /* = 0 */, glm::vec3 scale /* = 1 */)
{
	// Open file
	std::ifstream file(filePath);

	if (!file.is_open())
	{
		std::cout << "Failed to open '" << filePath << "'" << std::endl;
		return nullptr;
	}

	// Extract directory from file path
	std::string directory;
	const auto lastSlashIdX = filePath.rfind('/');
	if (std::string::npos != lastSlashIdX)
	{
		directory = filePath.substr(0, lastSlashIdX);
	}

	std::unordered_map<std::string, std::shared_ptr<Material>> materials;
	std::string selectedMaterial;
	
	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> textCoords;
	std::vector<glm::vec3> normals;

	std::unordered_map<std::string, std::vector<std::tuple<uint32_t, uint32_t, uint32_t>>> meshData;

	std::stringstream stream;
	std::string line;
	std::string prefix;

	while (std::getline(file, line))
	{
		stream.clear();
		stream.str(line);
		stream >> prefix;

		if (prefix == "mtllib")
		{
			// Material library file
			std::string fileName;
			stream >> fileName;

			materials = Material::LoadFromMtl(pShader, directory + '/' + fileName);
		}
		else if (prefix == "v")
		{
			// Position
			glm::vec3 vec;
			stream >> vec.x >> vec.y >> vec.z;
			positions.push_back(vec);
		}
		else if (prefix == "vt")
		{
			// Texture coordinate
			glm::vec2 vec;
			stream >> vec.x >> vec.y;
			textCoords.push_back(vec);
		}
		else if (prefix == "vn")
		{
			// Normal
			glm::vec3 vec;
			stream >> vec.x >> vec.y >> vec.z;
			normals.push_back(vec);
		}
		else if (prefix == "usemtl")
		{
			// Select material
			std::string materialName;
			stream >> selectedMaterial;
		}
		else if (prefix == "f")
		{
			// Face
			uint32_t posIndex, textCoordIndex, normalIndex;

			for (int i = 0; i < 3; i++)
			{
				stream >> posIndex;
				stream.ignore(1, '/');
				stream >> textCoordIndex;
				stream.ignore(1, '/');
				stream >> normalIndex;

				meshData[selectedMaterial].push_back({ posIndex, textCoordIndex, normalIndex });
			}
		}
	}

	// Construct meshes
	std::vector<std::shared_ptr<Mesh>> meshes;
	meshes.reserve(meshData.size());
	
	for (auto [material, vertexIndices] : meshData)
	{
		std::vector<Vertex> vertices;
		vertices.reserve(vertexIndices.size());
		
		std::vector<uint32_t> indices;
		indices.reserve(vertexIndices.size());

		uint32_t index = 0;
		for (auto [p, t, n] : vertexIndices)
		{
			Vertex v;
			v.position = positions[p - 1];
			v.textCoord = textCoords[t - 1];
			v.normal = normals[n - 1];
			
			vertices.push_back(v);
			indices.push_back(index++);
		}

		if (materials.find(material) == materials.end())
		{
			std::cout << "Cannot find material named '" << material << "'" << std::endl;
			return nullptr;
		}

		meshes.push_back(std::make_shared<Mesh>(vertices, indices, materials[material]));
	}

	return new Model(meshes, materials, position, rotation, scale);
}
