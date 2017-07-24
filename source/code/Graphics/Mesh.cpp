#include "Mesh.h"
#include "Gl.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, const std::vector<Texture>& textures)
{
	vertices_ = vertices;
	indices_ = indices;
	textures_ = textures;

	setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glGenBuffers(1, &ebo_);

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(Vertex), &vertices_[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(uint), &indices_[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); // Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1); // Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) sizeof(pm::vec3));
	glEnableVertexAttribArray(2); // Texture coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(pm::vec3) * 2));
	glEnableVertexAttribArray(3); // Tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(pm::vec3) * 2 + sizeof(pm::vec2)));
	glEnableVertexAttribArray(4); // Bitangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(pm::vec3) * 3 + sizeof(pm::vec2)));

	glBindVertexArray(0);
}

void Mesh::draw(const Shader* shader, uint num_instances, bool use_textures /*= true*/)
{
	if (use_textures && textures_.size() > 0)
	{
		for (uint i = 0; i < textures_.size(); i++)
		{
			glActiveTexture(GL_TEXTURE1 + i);
			std::string type = textures_[i].type;

			std::string name = "material." + type;
			shader->setInt(name.c_str(), i + 1);
			shader->setBool((name + "_bound").c_str(), true);

			glBindTexture(GL_TEXTURE_2D, textures_[i].id);
		}

		glActiveTexture(GL_TEXTURE0);
	}

	glBindVertexArray(vao_);
	if (num_instances >= 1)
	{
		glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0, num_instances);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, (GLsizei)indices_.size(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}
