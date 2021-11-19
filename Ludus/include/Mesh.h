#pragma once
#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, 
		std::vector<Texture>&& textures);

	void Draw(Shader& shader);
public:
	// mesh data
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<Texture> m_Textures;

	
private:
	void setupMesh();

private:
	VertexArray m_VAO;
	VertexBuffer m_VBO;
	VertexBufferLayout m_Layout;
	IndexBuffer m_IBO;
};