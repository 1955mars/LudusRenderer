#include "Mesh.h"
#include <iostream>

Mesh::Mesh(std::vector<Vertex>&& _vertices, std::vector<unsigned int>&& _indices, std::vector<Texture>&& _textures)
	:m_Vertices(std::move(_vertices)),
	m_Indices(std::move(_indices)),
	m_Textures(std::move(_textures)),
	m_VBO(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex)),
	m_IBO(&m_Indices[0], m_Indices.size())
{
	setupMesh();
}

void Mesh::Draw(Shader& shader)
{
	unsigned int diffuseIndex = 0;
	unsigned int specularIndex = 0;
	
	//std::cout << "texture count: draw: " << m_Textures[0].GetFilePath() << std::endl;

	//std::cout << "diffuse id:  " << m_Textures[0].GetId() << std::endl;
	//std::cout << "specular id:  " << m_Textures[1].GetId() << std::endl;
	//
	//shader.SetUniform1i("material.texture_diffuse0", 0);
	//shader.SetUniform1i("material.texture_specular0", 1);
	
	//m_Textures[0].Bind();
	//m_Textures[1].Bind(1);

	//shader.Bind();

	for (unsigned int i = 0; i < m_Textures.size(); i++)
	{
		std::string texName = "material.";
		
		if (m_Textures[i].GetTypeName() == "texture_diffuse")
			texName += "texture_diffuse" + std::to_string(diffuseIndex++);
		else if(m_Textures[i].GetTypeName() == "texture_specular")
			texName += "texture_specular" + std::to_string(specularIndex++);

		//std::cout << "texName: " << texName << "id: " << m_Textures[i].GetId() << std::endl;

		shader.SetUniform1i(texName, i);
		m_Textures[i].Bind(i);
	}

	m_VAO.Bind();
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
	m_VAO.Unbind();
}

void Mesh::setupMesh()
{
	m_Layout.Push<float>(3);
	m_Layout.Push<float>(3);
	m_Layout.Push<float>(2);

	m_VAO.AddBuffer(m_VBO, m_Layout);
}
