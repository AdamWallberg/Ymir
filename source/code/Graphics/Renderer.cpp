#include "Renderer.h"
#include "Core.h"
#include "Shader.h"
#include "GL.h"
#include "Window.h"
#include "Logger.h"
#include "ModelSystem.h"
#include "RawModel.h"
#include "Math/ymath.h"
#include "Camera/Camera.h"
#include "Skybox.h"

Renderer::Renderer(Engine* engine)
	: ISubSystem(engine)
{
	init();
}

Renderer::~Renderer()
{
	destroyFramebuffer();

	delete shader_quad_;
	delete shader_skybox_;
	delete shader_default_;

	delete skybox_;
}

void Renderer::init()
{
	// Create skybox
	skybox_ = newp Skybox("day", "jpg");

	initShaders();
	initFramebuffer();
	initScreenQuad();
}

void Renderer::initShaders()
{
	shader_default_ = newp Shader("default");
	shader_skybox_ = newp Shader("skybox");
	shader_quad_ = newp Shader("quad");
}

void Renderer::initFramebuffer()
{
	// Generate framebuffer
	glGenFramebuffers(1, &g_buffer_);
	glBindFramebuffer(GL_FRAMEBUFFER, g_buffer_);

	// Create position texture
	glGenTextures(1, &tex_position_);
	glBindTexture(GL_TEXTURE_2D, tex_position_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW->getWidth(), WINDOW->getHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_position_, 0);

	// Create normal texture
	glGenTextures(1, &tex_normal_);
	glBindTexture(GL_TEXTURE_2D, tex_normal_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WINDOW->getWidth(), WINDOW->getHeight(), 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, tex_normal_, 0);

	// Create color texture
	glGenTextures(1, &tex_albedo_spec_);
	glBindTexture(GL_TEXTURE_2D, tex_albedo_spec_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WINDOW->getWidth(), WINDOW->getHeight(), 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, tex_albedo_spec_, 0);

	// Create object id texture
	glGenTextures(1, &tex_object_id_);
	glBindTexture(GL_TEXTURE_2D, tex_object_id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, WINDOW->getWidth(), WINDOW->getHeight(), 0, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, tex_object_id_, 0);

	uint attachments[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Create render buffer object
	glGenRenderbuffers(1, &render_buffer_);
	glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WINDOW->getWidth(), WINDOW->getHeight());

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, render_buffer_);

	// Check for errors
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		LOG_ERROR("Framebuffer not complete!", Logger::FLAG_GRAPHICS);
		ymAssert(false);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::initScreenQuad()
{
	static const float quadVertices[] =
	{
		-1.0f, 1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f, 0.0f,

		-1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &screen_quad_vao_);
	glGenBuffers(1, &screen_quad_vbo_);
	glBindVertexArray(screen_quad_vao_);
	glBindBuffer(GL_ARRAY_BUFFER, screen_quad_vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
}

void Renderer::destroyFramebuffer()
{
	glDeleteBuffers(1, &render_buffer_);
	glDeleteTextures(1, &tex_albedo_spec_);
	glDeleteTextures(1, &tex_normal_);
	glDeleteTextures(1, &tex_position_);
	glDeleteFramebuffers(1, &g_buffer_);
}

void Renderer::render()
{
	Camera* camera = MainCam::get();
	const Color& clear_color = camera->clear_color_;

	// GEOMETRY RENDER PASS
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	glDisable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glBindFramebuffer(GL_FRAMEBUFFER, g_buffer_);
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glClear(camera->clear_flags_);
	
	shader_default_->bind();
	// Setup shader uniform matrices
	const pm::mat4 view_matrix = camera->view_matrix_;
	const pm::mat4 proj_matrix = camera->projection_matrix_;
	shader_default_->setMat4("view_mat", view_matrix);
	shader_default_->setMat4("proj_mat", proj_matrix);
	std::map<RawModel*, std::pair<uint, std::vector<Model*>>>& models = MODEL_SYSTEM->getModels();
	for (auto& it : models)
	{
		uint numInstances = UINT_S(it.second.second.size());
		RawModel* raw_model = it.first;
		raw_model->draw(shader_default_, numInstances);
	}

	// FULLSCREEN QUAD RENDER PASS
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_albedo_spec_);

	shader_quad_->bind();
	shader_quad_->setInt("uTexture", 0);

	glBindVertexArray(screen_quad_vao_);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// Blit g_buffer depth to backbuffer depth, so we can forward render after previous passes
	glBindFramebuffer(GL_READ_FRAMEBUFFER, g_buffer_);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, WINDOW->getWidth(), WINDOW->getHeight(), 0, 0, WINDOW->getWidth(), WINDOW->getHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Render skybox
	shader_skybox_->bind();
	skybox_->draw(shader_skybox_);
}

void Renderer::resize()
{
	const int width = WINDOW->getWidth();
	const int height = WINDOW->getHeight();

	// Resize framebuffer
	glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, tex_position_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);

	glBindTexture(GL_TEXTURE_2D, tex_normal_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);

	glBindTexture(GL_TEXTURE_2D, tex_albedo_spec_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

	glBindTexture(GL_TEXTURE_2D, tex_object_id_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, nullptr);
	
	glViewport(0, 0, width, height);
	float aspect = width / FLOAT_S(height);
	MainCam::get()->aspect_ = aspect;
	MainCam::get()->updateProjection();
}

uint Renderer::getObjectIDAt(uint x, uint y)
{
	glBindTexture(GL_TEXTURE_2D, tex_albedo_spec_);
	uint pixel;
	int size = sizeof(uint);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, g_buffer_);
	glReadBuffer(GL_COLOR_ATTACHMENT3);
	glReadPixels(x, WINDOW->getHeight() - y, 1, 1, GL_RED_INTEGER, GL_UNSIGNED_INT, &pixel);
	return pixel;
}