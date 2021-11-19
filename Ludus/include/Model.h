#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_map>

#include "Mesh.h"

class Model
{
public:
	Model(const char* path);
	void Draw(Shader& shader);
private:
	std::vector<Mesh> m_Meshes;
	std::string m_Directory;
	std::vector<Texture> loadedTextures;
	std::unordered_map<std::string, int> loadedTexturesMap;

	void loadModel(const std::string& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);
};
