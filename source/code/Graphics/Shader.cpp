#include "Shader.h"
#include "GL.h"
#include <vector>
#include <fstream>
#include "Logger.h"

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
		geometry_name = geometry_name + "_v.glsl";
	fragment_name = fragment_name + "_v.glsl";

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
