#pragma once

#include "Types.h"
#include "Shader.h"

class Camera;
class RawModel;

class Skybox
{
public:
	Skybox(std::string name, std::string format);
	~Skybox();
	void draw(const Shader* shader);
	uint getCubemapID() const { return cubemap_id_; }
private:
	uint loadCubemap(std::string faces[6]);
	uint cubemap_id_;
	RawModel* model_;
};