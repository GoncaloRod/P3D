#include "pch.h"

#include "Mesh.h"

#include "Material.h"
#include "Renderer/VertexArray.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/IndexBuffer.h"
#include "Renderer/Shader.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, std::shared_ptr<Material> pMaterial)
	: m_pMaterial(pMaterial), m_Vertices(vertices), m_Indices(indices)
{
	m_pVAO = std::make_shared<VertexArray>();
	
	m_pVBO = std::make_shared<VertexBuffer>(&m_Vertices[0].position.x, static_cast<uint32_t>(m_Vertices.size() * Vertex::GetElementCount()));
	m_pVBO->SetLayout(Vertex::GetBufferLayout());
	
	m_pIBO = std::make_shared<IndexBuffer>(&m_Indices[0], static_cast<uint32_t>(m_Indices.size()));

	m_pVAO->AddVertexBuffer(m_pVBO);
	m_pVAO->SetIndexBuffer(m_pIBO);
}

void Mesh::Draw(glm::mat4 modelMat) const
{
	m_pMaterial->Bind();
	m_pMaterial->GetShader()->SetMat4("u_Model", modelMat);

	m_pVAO->Bind();

	glDrawElements(GL_TRIANGLES, m_pVAO->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
