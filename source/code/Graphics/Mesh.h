#pragma once

#include "Math/yMath.h"
#include "Shader.h"
#include "Types.h"
#include <vector>
#include <assimp/types.h>

struct Vertex
{
	pm::vec3 position;
	pm::vec3 normal;
	pm::vec2 tex_coords;
	pm::vec3 tangent;
	pm::vec3 bitangent;
};

struct Texture
{
	uint id;
	std::string type;
	aiString name;
};

class Mesh
{
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, const std::vector<Texture>& textures);
	void draw(const Shader* shader, uint num_instances, bool use_textures = true);
	uint getVAO() const { return vao_; }
private:
	void setupMesh();

	uint vao_;
	uint vbo_;
	uint ebo_;

	std::vector<Vertex> vertices_;
	std::vector<uint> indices_;
	std::vector<Texture> textures_;
};