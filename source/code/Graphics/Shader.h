#pragma once

#include "Types.h"

class Shader
{
public:
	Shader(const std::string& name);
	Shader(const std::string& vertex_name, const std::string& fragment_name);
	Shader(const std::string& vertex_name, const std::string& geometry_name, const std::string& fragment_name);
	~Shader();
	void bind();
/*
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setVec2(const std::string& name, glm::vec2 value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setVec4(const std::string& name, glm::vec4 value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;*/
	uint getID() const { return id_; }
private:
	void setupProgram(std::string vertex_name, std::string geometry_name, std::string fragment_name);
	uint loadShaderFromFile(std::string directory, std::string file_name, int shader_type);

	uint id_;
};