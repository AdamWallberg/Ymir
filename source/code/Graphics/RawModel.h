#pragma once

#include "Shader.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include <assimp/scene.h>

class RawModel
{
public:
	RawModel(std::string name);
	void draw(const Shader* shader, uint num_instances, bool use_textures = true);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string type_name);

	std::vector<Texture> loaded_textures_;
	std::string path_;
	std::string directory_;
	std::vector<Mesh> meshes_;
};