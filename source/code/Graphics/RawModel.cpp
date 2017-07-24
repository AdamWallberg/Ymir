#include "RawModel.h"
#include "Logger.h"
#include "GL.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <SOIL.h>

RawModel::RawModel(std::string name)
{
	LOG("Creating model: " + name, Logger::FLAG_IO);
	loadModel(name);
	path_ = name;
}

void RawModel::draw(const Shader* shader, uint num_instances, bool use_textures)
{
	for (Mesh& mesh : meshes_)
	{
		mesh.draw(shader, num_instances, use_textures);
	}
}

void RawModel::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		LOG_ERROR("ASSIMP: " + std::string(importer.GetErrorString()), Logger::FLAG_IO);
		return;
	}
	directory_ = path.substr(0, path.find_last_of('/')) + '/';
	processNode(scene->mRootNode, scene);
}

void RawModel::processNode(aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes_.push_back(processMesh(mesh, scene));
	}

	for (uint i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh RawModel::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<uint> indices;
	std::vector<Texture> textures;

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		pm::vec3 position;
		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;
		vertex.position = position;

		pm::vec3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		vertex.normal = normal;

		if (mesh->mTangents)
		{
			pm::vec3 tangent;
			tangent.x = mesh->mTangents[i].x;
			tangent.y = mesh->mTangents[i].y;
			tangent.z = mesh->mTangents[i].z;
			vertex.tangent = tangent;

			pm::vec3 bitangent;
			bitangent.x = mesh->mBitangents[i].x;
			bitangent.y = mesh->mBitangents[i].y;
			bitangent.z = mesh->mBitangents[i].z;
			vertex.bitangent = bitangent;
		}

		if (mesh->mTextureCoords[0])
		{
			pm::vec2 uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			vertex.tex_coords = uv;
		}
		else
		{
			vertex.tex_coords = pm::vec2(0.f, 0.f);
		}

		vertices.push_back(vertex);
	}

	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		// Check if textures are embedded
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normal");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		std::vector<Texture> reflectionMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_reflection");
		textures.insert(textures.end(), reflectionMaps.begin(), reflectionMaps.end());
		std::vector<Texture> displacementMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_displacement");
		textures.insert(textures.end(), displacementMaps.begin(), displacementMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> RawModel::loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string type_name)
{
	std::vector<Texture> textures;
	for (uint i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString name;
		material->GetTexture(type, i, &name);

		bool skip = false;
		for (uint j = 0; j < loaded_textures_.size(); j++)
		{
			if (std::strcmp(loaded_textures_[j].name.C_Str(), name.C_Str()) == 0)
			{
				textures.push_back(loaded_textures_[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			Texture texture;
			std::string path = directory_ + name.C_Str();

			// Create texture
			int width, height, channels;
			uint8* data = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_RGBA);
			glGenTextures(1, &texture.id);
			glBindTexture(GL_TEXTURE_2D, texture.id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glGenerateMipmap(GL_TEXTURE_2D);
			delete data;

			texture.type = type_name;
			texture.name = name;
			textures.push_back(texture);
		}
	}
	return textures;
}
