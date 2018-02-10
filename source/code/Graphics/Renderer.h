#pragma once

#include "Types.h"

class Shader;
class Window;
class ModelSystem;
class Skybox;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void render();
	void resize();
private:
	void init();
	void initShaders();
	void initFramebuffer();
	void initScreenQuad();

	void destroyFramebuffer();

	// Shaders
	Shader* shader_default_;
	Shader* shader_skybox_;
	Shader* shader_quad_;

	// Framebuffer
	uint g_buffer_;
	uint tex_position_;
	uint tex_normal_;
	uint tex_albedo_spec_;
	uint render_buffer_;

	// Fullscreen quad
	uint screen_quad_vao_;
	uint screen_quad_vbo_;

	// Skybox
	Skybox* skybox_;

	// Misc
	Window* window_;
	ModelSystem* model_sytem_;
};