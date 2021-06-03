#pragma once

#include "Vertex.h"

#include "glm/mat4x4.hpp"
#include "glm/gtx/associated_min_max.hpp"
#include "glm/gtx/associated_min_max.hpp"
#include "glm/gtx/associated_min_max.hpp"
#include "glm/gtx/associated_min_max.hpp"

class VertexBuffer;
class IndexBuffer;
class VertexArray;
class Material;

class Mesh
{
public:

	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::shared_ptr<Material> pMaterial);
	~Mesh() = default;

	/**
	 * Draw this mesh.
	 *
	 * @param modelMat Model matrix to use when drawing.
	 */
	void Draw(glm::mat4 modelMat) const;

private:

	std::shared_ptr<VertexBuffer> m_pVBO;
	std::shared_ptr<IndexBuffer> m_pIBO;
	std::shared_ptr<VertexArray> m_pVAO;
	std::shared_ptr<Material> m_pMaterial;
	
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
};
