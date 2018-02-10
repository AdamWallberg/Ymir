#include "Skybox.h"
#include "Camera/Camera.h"
#include "GL.h"
#include "Logger.h"
#include "RawModel.h"
#include "Core.h"

#include <SOIL.h>

Skybox::Skybox(std::string name, std::string format)
{
	// Load textures
	std::string face_names[6] = { 
		"right", "left", 
		"top", "bottom", 
		"back", "front"
	};
	for (uint i = 0; i < 6; i++)
	{
		face_names[i] = 
			"data/skybox/" + name + "/" + face_names[i] + "." + format;
	}

	cubemap_id_ = loadCubemap(face_names);

	// Load box model
	model_ = newp RawModel("data/models/debug/cube.obj");

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

Skybox::~Skybox()
{
	delete model_;
}

void Skybox::draw(const Shader* shader)
{
	glDisable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);

	// Get view and proj matrices
	Camera* camera = MainCam::get();
	pm::mat4 view = camera->view_matrix_;
	view.position = pm::vec3::zero;
	const pm::mat4 proj = camera->projection_matrix_;
	shader->setMat4("view_mat", view);
	shader->setMat4("proj_mat", proj);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id_);
	model_->draw(shader, 1);
	
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

uint Skybox::loadCubemap(std::string faces[6])
{
	uint texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);
	int width, height, channels;

	for (uint i = 0; i < 6; i++)
	{
		uint8* dataPtr = SOIL_load_image(
			faces[i].c_str(), 
			&width, 
			&height, 
			&channels, 
			SOIL_LOAD_RGB);
		if (!dataPtr)
		{
			LOG_ERROR(
				"Failed to load texture: " + faces[i], 
				Logger::FLAG_GRAPHICS);
		}
		else
		{
			glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
				0, 
				GL_RGB, 
				width, 
				height, 
				0, 
				GL_RGB, 
				GL_UNSIGNED_BYTE, 
				dataPtr);
			delete dataPtr;
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture_id;
}