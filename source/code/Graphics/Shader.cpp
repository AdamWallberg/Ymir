#include "Shader.h"
#include "GL.h"
#include <vector>
#include <fstream>
#include "Logger.h"
#include "Core.h"

Shader::Shader(const std::string& name)
{
	setupProgram(name, "", name);
}

Shader::Shader(const std::string& vertex_name, const std::string& fragment_name)
{
	setupProgram(vertex_name, "", fragment_name);
}

Shader::Shader(const std::string& vertex_name, const std::string& geometry_name, const std::string& fragment_name)
{
	setupProgram(vertex_name, geometry_name, fragment_name);
}

Shader::~Shader()
{
	glDeleteProgram(id_);
}

void Shader::bind()
{
	glUseProgram(id_);
}

void Shader::setupProgram(std::string vertex_name, std::string geometry_name, std::string fragment_name)
{
	std::string directory = "data/shaders/";

	bool has_geoemetry = geometry_name != "";

	// Setup shader names
	vertex_name = vertex_name + "_v.glsl";
	if(has_geoemetry) // We might not have a geometry shader
		geometry_name = geometry_name + "_g.glsl";
	fragment_name = fragment_name + "_f.glsl";

	// Load shaders
	uint vertex_id = loadShaderFromFile(directory, vertex_name, GL_VERTEX_SHADER);
	uint geoemetry_id = has_geoemetry ? loadShaderFromFile(directory, geometry_name, GL_GEOMETRY_SHADER) : 0;
	uint fragment_id = loadShaderFromFile(directory, fragment_name, GL_FRAGMENT_SHADER);


	// Create and link the program
	id_ = glCreateProgram();
	glAttachShader(id_, vertex_id);
	if (has_geoemetry)
		glAttachShader(id_, geoemetry_id);
	glAttachShader(id_, fragment_id);
	glLinkProgram(id_);

	// Check for errors
	int result = false;
	int info_log_length;
	glGetProgramiv(id_, GL_LINK_STATUS, &result);
	glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		std::vector<char> error_message(info_log_length + 1);
		glGetProgramInfoLog(id_, info_log_length, nullptr, &error_message[0]);
		LOG_ERROR(&error_message[0], Logger::FLAG_GRAPHICS);
	}

	// Detach shaders
	glDetachShader(id_, vertex_id);
	if(has_geoemetry)
		glDetachShader(id_, geoemetry_id);
	glDetachShader(id_, fragment_id);
	glDeleteShader(vertex_id);
	if (has_geoemetry)
		glDeleteShader(geoemetry_id);
	glDeleteShader(fragment_id);
}

uint Shader::loadShaderFromFile(std::string directory, std::string file_name, int shader_type)
{
	LOG("Loading shader: " + file_name, Logger::FLAG_GRAPHICS);

	// Read code
	std::string code;
	std::string file_path = directory + file_name;
	std::ifstream stream(file_path, std::ios::in);
	if (!stream.is_open())
	{
		LOG_ERROR("Failed to open shader: " + file_path);
		return 0;
	}
	else
	{
		std::string line = "";
		while (getline(stream, line))
			code += "\n" + line;
		stream.close();
	}

	// Create shader
	uint id = glCreateShader(shader_type);
	int result = false;
	int info_log_length;

	// Compile shader
	const char* source_pointer = code.c_str();
	glShaderSource(id, 1, &source_pointer, nullptr);
	glCompileShader(id);

	// Check for errors
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &info_log_length);
	if (info_log_length > 0)
	{
		std::vector<char> error_message(info_log_length + 1);
		glGetShaderInfoLog(id, info_log_length, nullptr, &error_message[0]);
		LOG_ERROR(&error_message[0], Logger::FLAG_GRAPHICS);
	}

	return id;
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setUInt(const std::string& name, uint value) const
{
	glUniform1ui(glGetUniformLocation(id_, name.c_str()), value);
}


void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, pm::vec2 value) const
{
	glUniform2f(glGetUniformLocation(id_, name.c_str()), value.x, value.y);
}

void Shader::setVec3(const std::string& name, pm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(id_, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVec4(const std::string& name, pm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(id_, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMat4(const std::string& name, pm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, &value[0]);
}